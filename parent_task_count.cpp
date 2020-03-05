#include "schedule.hpp"

/*
	Get Number of task dependencies (or parents)
	for each task
 */
std::vector<int> parent_task_count(const adj_list &graph) {
	std::vector<int> parent_tasks(graph.size(), 0);
	for (auto &children : graph) {
		for (auto &child : children) {
			++parent_tasks[child];
		}
	}
	return parent_tasks;
}
