#include "task.hpp"

std::vector<task> read_tasks(std::ifstream &stream) {
	std::vector<task> list_of_tasks;
	int id = 0;
	double W_HP, W_LP, a_LP, alpha_LP;
	while (stream >> W_HP >> W_LP >> a_LP >> alpha_LP) {
		task new_task = task(id++, W_HP, W_LP, a_LP, alpha_LP);
		list_of_tasks.push_back(new_task);
	}
	return list_of_tasks;
}
