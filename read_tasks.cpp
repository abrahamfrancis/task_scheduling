#include "task.hpp"

std::vector<task> read_tasks(std::ifstream &stream) {
	std::vector<task> list_of_tasks;
	int count;
	stream >> count;
	double W_HP, W_LP, a_LP, alpha_LP;
	char buff;
	for (int id = 0; id < count; ++id) {
		stream >> buff >> W_HP >> buff >> W_LP >> buff >> a_LP >> buff >> alpha_LP;
		task new_task = task(id, W_HP, W_LP, a_LP, alpha_LP);
		list_of_tasks.push_back(new_task);
	}
	return list_of_tasks;
}
