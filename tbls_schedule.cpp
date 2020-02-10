#include "schedule.hpp"

schedule tbls_schedule(const std::vector<task> &tasks, const adj_list &graph) {
	schedule tbls;
	std::vector<int> parent_tasks = parent_task_count(graph);
	return tbls;
}
