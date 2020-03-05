#include "schedule.hpp"
#include "task.hpp"

void clear_tasks(ready_list &ready_tasks, const std::vector<task> &tasks,
                 const std::vector<int> &adjacent, std::vector<int> &parent_tasks)
/*
	Reduces parent_tasks (left to execute)
	for each adjacent node which are tasks that are
	dependent on the parent_task
	Adds tasks with no dependencies to queue
 */
{
	for (int i : adjacent) {
		if (--parent_tasks[i] == 0) {
			ready_tasks.push(tasks[i]);
		}
	}
}
