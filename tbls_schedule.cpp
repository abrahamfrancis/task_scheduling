#include "schedule.hpp"
#include "task.hpp"

schedule tbls_schedule(const std::vector<task> &tasks, const adj_list &graph,
                       double threshold=tbls_threshold)
{
	schedule tbls;
	std::vector<int> parent_tasks = parent_task_count(graph);
	return tbls;
}
