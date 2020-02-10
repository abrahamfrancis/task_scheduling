#ifndef _SCHEDULE_

#define _SCHEDULE_

#include <vector>
#include "adj_list.hpp"
#include "task.hpp"

const unsigned int MAX_DUR = 100; //100ms

typedef struct {
	int id;
	double start, size;
} slot;

class schedule {
private:
	std::vector<slot> HP, LP;

	void display(std::ofstream &stream, std::vector<slot> &P) {
		for (unsigned int i = 0; i < P.size(); ++i) {
			if (i != 0) stream << ' ';
			stream << P[i].id << ' ' << P[i].start << ' ' << P[i].size;
		}
		stream << std::endl;
	}

public:
	void add_HP_slot(int id, double start, double size) {
		HP.push_back({id, start, size});
	}

	void add_LP_slot(int id, double start, double size) {
		LP.push_back({id, start, size});
	}

	void show(std::ofstream &stream) {
		display(stream, HP);
		display(stream, LP);
	}
};

std::vector<int> parent_task_count(const adj_list &);

// Largest Task First
schedule ltf_schedule(const std::vector<task> &, const adj_list &);

// Threshold-based List Scheduling
schedule tbls_schedule(const std::vector<task> &, const adj_list &);

#endif
