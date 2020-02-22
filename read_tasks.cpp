#include "task.hpp"

std::vector<task> read_tasks(std::ifstream &stream) {
	std::vector<task> list_of_tasks;
	int count;
	stream >> count;
	double W_HP, W_LP, a_LP, alpha_LP;
	double C_HP, C_LP, A, tscale, pscale, inv_ratio;
	char buff;
	for (int id = 0; id < count; ++id) {
		stream >> buff >> C_HP >> buff >> tscale >> buff >> inv_ratio;
		pscale = 1/(tscale*inv_ratio);
		C_LP = tscale * C_HP;
		W_HP = C_HP/f_HP_max;
		W_LP = C_LP/f_LP_max;
		a_LP = pscale * a_HP;
		alpha_LP = pscale * alpha_HP;
		task new_task = task(id, W_HP, W_LP, a_LP, alpha_LP);
		list_of_tasks.push_back(new_task);
	}
	return list_of_tasks;
}
