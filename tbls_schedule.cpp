#include "schedule.hpp"
#include "task.hpp"

schedule tbls_schedule(const std::vector<task> &tasks, const adj_list &graph, double threshold)
{
	schedule tbls;
	std::vector<int> parent_tasks = parent_task_count(graph);
	double max_util = threshold * MAX_DUR;
	ready_list ready_tasks, wait_tasks;

	/*
		Fill ready tasks with orphan tasks -
		ones with no dependencies
	 */
	for (unsigned int i = 0; i < parent_tasks.size(); ++i) {
		if (parent_tasks[i] == 0) {
			ready_tasks.push(tasks[i]);
		}
	}

	double lp_util = 0.0;
	int last_lp = -1, last_hp = -1;
	while (! ready_tasks.empty()) {
		task ready = ready_tasks.top();
		ready_tasks.pop();

		lp_util += ready.lp_size();
		if ((tbls.lpt() + ready.lp_size() <= MAX_DUR) && lp_util <= max_util) {
		// LP Slot is Free and current task will not exceed MAX_DUR or UTILIZATION THRESHOLD
			tbls.add_LP_slot(ready);
			if (last_lp != -1) clear_tasks(wait_tasks, tasks, graph[last_lp], parent_tasks);
			last_lp = ready.get_id();
		} else {
			lp_util -= ready.lp_size();
			tbls.add_HP_slot(ready);
			if (last_hp != -1) clear_tasks(wait_tasks, tasks, graph[last_hp], parent_tasks);
			last_hp = ready.get_id();
		}

		if (ready_tasks.empty()) {
			tbls.wait();
			if (last_lp != -1) clear_tasks(wait_tasks, tasks, graph[last_lp], parent_tasks);
			if (last_hp != -1) clear_tasks(wait_tasks, tasks, graph[last_hp], parent_tasks);
			last_lp = last_hp = -1;
			std::swap(ready_tasks, wait_tasks);
		}
	}
	return tbls;
}
