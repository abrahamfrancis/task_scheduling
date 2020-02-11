#ifndef _TASKS_

#define _TASKS_

#include <fstream>
#include <vector>

const double f_HP_max  = 1.0,
             f_LP_max  = 0.8,
             P_HP_idle = 0.05,
             P_LP_idle = 0.02,
             tbls_threshold = 0.65,
             a_HP = 1.0,
             alpha_HP = 0.1;

class task {
private:
	int id;
	double W_HP, W_LP, a_LP, alpha_LP;

public:
	task(int id, double W_HP, double W_LP, double a_LP, double alpha_LP) {
		this->id       = id;
		this->W_HP     = W_HP;
		this->W_LP     = W_LP;
		this->a_LP     = a_LP;
		this->alpha_LP = alpha_LP;
	}

	double size() const {
		return W_HP;
	}

	double lp_size() const {
		return W_LP;
	}

	int get_id() const {
		return id;
	}

	double power_lp(double f=f_LP_max) const {
		double f_cubed = f * f * f;
		return a_LP * f_cubed + alpha_LP;
	}

	double power_hp(double f=f_HP_max) const {
		double f_cubed = f * f * f;
		return a_HP * f_cubed + alpha_HP;
	}

	void show() {
		std::ofstream out("sample", std::ios::app);
		out << "W_HP: "     << W_HP     << '\t'
		    << "W_LP: "     << W_LP     << '\t'
			<< "a_LP: "     << a_LP     << '\t'
			<< "alpha_LP: " << alpha_LP << '\t'
			<< std::endl;
		out.close();
	}
};

typedef std::pair<int, int> edge;

std::vector<task> read_tasks(std::ifstream &);
std::vector<edge> read_edges(std::ifstream &);

#endif
