#include "schedule.hpp"
#include "task.hpp"

#include <queue>

struct compare_by_size {
	bool operator()(const task &t1, const task &t2) {
		return t1.size() < t2.size();
	}
};

typedef std::priority_queue<task, std::vector<task>, compare_by_size> ready_list;

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

schedule tbls_schedule(const std::vector<task> &tasks, const adj_list &graph,
                       double threshold=tbls_threshold)
{
	schedule tbls;
	std::vector<int> parent_tasks = parent_task_count(graph);
	ready_list ready_tasks;
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
		if ((tbls.lpt() <= tbls.hpt()) && (tbls.lpt() + ready.lp_size() <= MAX_DUR)) {
			tbls.add_LP_slot(ready);
			if (last_lp != -1) clear_tasks(ready_tasks, tasks, graph[last_lp], parent_tasks);
			last_lp = ready.get_id();
			time = tbls.lpt();

			if (tbls.lpt() >= tbls.hpt() && last_hp != -1) {
				clear_tasks(ready_tasks, tasks, graph[last_hp], parent_tasks);
				last_hp = -1;
			}
		} else {
			tbls.add_HP_slot(ready);
			if (last_hp != -1) clear_tasks(ready_tasks, tasks, graph[last_hp], parent_tasks);
			last_hp = ready.get_id();
			time = tbls.hpt();

			if (tbls.hpt() >= tbls.lpt() && last_lp != -1) {
				clear_tasks(ready_tasks, tasks, graph[last_lp], parent_tasks);
				last_lp = -1;
			}
		}

		if (ready_tasks.empty()) {
			tbls.wait();
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
	return tbls;
}
