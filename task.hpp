#ifndef _TASKS_

#define _TASKS_

#include <fstream>
#include <vector>

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
