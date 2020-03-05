#include "schedule.hpp"
#include "task.hpp"

schedule tbls_schedule(const std::vector<task> &tasks, const adj_list &graph, double threshold)
{
	schedule tbls;
	std::vector<int> parent_tasks = parent_task_count(graph);
	double max_util = threshold * MAX_DUR;
	return tbls;
}
