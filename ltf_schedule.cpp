#include <queue>

#include "schedule.hpp"
#include "task.hpp"

typedef std::priority_queue<task, std::vector<task>, compare_task_by_size> ready_list;

void clear_tasks(ready_list &ready_tasks, const std::vector<task> &tasks,
                 const std::vector<int> &adjacent, std::vector<int> &parent_tasks)
/*	Reduces parent_tasks (left to execute)
	for each adjacent node which are tasks dependent on the parent_task

	Adds tasks with no dependencies to queue
 */
{
	for (int i : adjacent) {
		if (--parent_tasks[i] == 0) {
			ready_tasks.push(tasks[i]);
		}
	}
}

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
		double time;

		if ((ltf.lpt() <= ltf.hpt()) && (ltf.lpt() + ready.lp_size() <= MAX_DUR)) {
		// LP Slot is Free and current task will not exceed MAX_DUR
			ltf.add_LP_slot(ready);
			if (last_lp != -1) clear_tasks(ready_tasks, tasks, graph[last_lp], parent_tasks);
			last_lp = ready.get_id();
			time = ltf.lpt();

			if (ltf.lpt() >= ltf.hpt() && last_hp != -1) {
				clear_tasks(ready_tasks, tasks, graph[last_hp], parent_tasks);
				last_hp = -1;
			}
		} else {
		// Add task to HP Slot
			ltf.add_HP_slot(ready);
			if (last_hp != -1) clear_tasks(ready_tasks, tasks, graph[last_hp], parent_tasks);
			last_hp = ready.get_id();
			time = ltf.hpt();

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
