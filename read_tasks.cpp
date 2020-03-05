#include "task.hpp"

std::vector<task> read_tasks(std::ifstream &stream) {
	std::vector<task> list_of_tasks;
	double sum;
	stream >> sum;
	int count;
	stream >> count;
	double C_HP, C_LP, A, tscale, pscale, inv_ratio, sigma_W_LP = 0.0;
	char buff;
	std::vector<double> W_HP(count), W_LP(count), a_LP(count), alpha_LP(count);
	for (int id = 0; id < count; ++id) {
		stream >> buff >> C_HP >> buff >> tscale >> buff >> inv_ratio;
		pscale = 1/(tscale*inv_ratio);
		C_LP = tscale * C_HP;
		W_HP[id] = C_HP/f_HP_max;
		W_LP[id] = C_LP/f_LP_max;
		a_LP[id] = pscale * a_HP;
		alpha_LP[id] = pscale * alpha_HP;

		sigma_W_LP += W_LP[id];
	}
	double s_f = sum/sigma_W_LP;
	for (int id = 0; id < count; ++id) {
		task new_task = task(id, W_HP[id]*s_f, W_LP[id]*s_f, a_LP[id], alpha_LP[id]);
		list_of_tasks.push_back(new_task);
	}
	return list_of_tasks;
}
