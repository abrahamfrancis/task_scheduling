#ifndef _SCHEDULE_

#define _SCHEDULE_

#include <vector>
#include <iomanip>
#include "adj_list.hpp"
#include "task.hpp"

const unsigned int MAX_DUR = 100; //100ms

typedef struct {
	double start;
	task t;
	double freq;
} slot;

class schedule {
private:
	std::vector<slot> HP, LP;

	void display(std::ofstream &stream, std::vector<slot> &P, char type) {
		for (unsigned int i = 0; i < P.size(); ++i) {
			if (i != 0) stream << ' ';
			double size;
			if (type == 'L') {
				size = P[i].t.lp_size() * P[i].freq/f_LP_max;
			} else {
				size = P[i].t.size() * P[i].freq/f_HP_max;
			}
			stream << P[i].t.get_id() << ' ' << P[i].start << ' ' << size << ' ' << P[i].freq;
		}
		stream << std::endl;
	}

	double energy_for(std::vector<slot> &P, double P_idle, char type, double &ended) {
		double E = 0.0;
		for (unsigned int i = 0; i < P.size(); ++i) {
			if (ended != P[i].start) {
				E += (P[i].start - ended) * P_idle;
			}
			double size;
			if (type == 'L') {
				size = P[i].t.lp_size() * P[i].freq/f_LP_max;
				E += size * P[i].t.power_lp();
			} else {
				size = P[i].t.size() * P[i].freq/f_HP_max;
				E += size * P[i].t.power_hp();
			}
			ended = P[i].start + size;
		}
		return E;
	}


public:
	void add_HP_slot(double start, task t, double freq=f_HP_max) {
		HP.push_back({start, t, freq});
	}

	void add_LP_slot(double start, task t, double freq=f_LP_max) {
		LP.push_back({start, t, freq});
	}

	double energy() {
		double E = 0.0;

		if (LP.size() != 0 && HP.size() != 0) {
			double lp_started = LP[0].start,
			       hp_started = HP[0].start;
			if (hp_started > lp_started) {
				E += (lp_started - hp_started) * P_HP_idle;
			} else if (lp_started > hp_started) {
				E += (hp_started - lp_started) * P_LP_idle;
			}
		}

		double lp_ended = 0.0, hp_ended = 0.0;
		E += energy_for(LP, P_LP_idle, 'L', lp_ended)
		  +  energy_for(HP, P_HP_idle, 'H', hp_ended);

		if (lp_ended > hp_ended) {
			E += (lp_ended - hp_ended) * P_HP_idle;
		} else if (hp_ended > lp_ended) {
			E += (hp_ended - lp_ended) * P_LP_idle;
		}
		return E;
	}

	void show(std::ofstream &stream) {
		display(stream, HP, 'H');
		display(stream, LP, 'L');
		stream << std::setprecision(15) << std::fixed << energy() << std::endl;
	}
};

std::vector<int> parent_task_count(const adj_list &);

// Largest Task First
schedule ltf_schedule(const std::vector<task> &, const adj_list &);

// Threshold-based List Scheduling
schedule tbls_schedule(const std::vector<task> &, const adj_list &);

schedule contingency_schedule();

#endif
