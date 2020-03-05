#include "schedule.hpp"
#include "task.hpp"

schedule ltf_schedule(const std::vector<task> &tasks, const adj_list &graph)
{
	schedule ltf;
	std::vector<int> parent_tasks = parent_task_count(graph);
	ready_list ready_tasks;

	/*
		Fill ready tasks with orphan tasks -
		ones with no dependencies
	 */
	for (unsigned int i = 0; i < parent_tasks.size(); ++i) {
		if (parent_tasks[i] == 0) {
			ready_tasks.push(tasks[i]);
		}
	}

	int last_lp = -1, last_hp = -1;
	while (! ready_tasks.empty()) {
		task ready = ready_tasks.top();
		ready_tasks.pop();

		if ((ltf.lpt() <= ltf.hpt()) && (ltf.lpt() + ready.lp_size() <= MAX_DUR)) {
		// LP Slot is Free and current task will not exceed MAX_DUR
			ltf.add_LP_slot(ready);
			if (last_lp != -1) clear_tasks(ready_tasks, tasks, graph[last_lp], parent_tasks);
			last_lp = ready.get_id();

			if (ltf.lpt() >= ltf.hpt() && last_hp != -1) {
				clear_tasks(ready_tasks, tasks, graph[last_hp], parent_tasks);
				last_hp = -1;
			}
		} else {
		// Add task to HP Slot
			ltf.add_HP_slot(ready);
			if (last_hp != -1) clear_tasks(ready_tasks, tasks, graph[last_hp], parent_tasks);
			last_hp = ready.get_id();

			if (ltf.hpt() >= ltf.lpt() && last_lp != -1) {
				clear_tasks(ready_tasks, tasks, graph[last_lp], parent_tasks);
				last_lp = -1;
			}
		}

		if (ready_tasks.empty()) {
			ltf.wait();
			if (last_lp != -1) {
				clear_tasks(ready_tasks, tasks, graph[last_lp], parent_tasks);
				last_lp = -1;
			}
			if (last_hp != -1) {
				clear_tasks(ready_tasks, tasks, graph[last_hp], parent_tasks);
				last_hp = -1;
			}
		}
	}
	return ltf;
}
