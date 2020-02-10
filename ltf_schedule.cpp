#include "schedule.hpp"
#include "task.hpp"

#include <queue>

struct compare_by_size {
	bool operator()(const task &t1, const task &t2) {
		return t1.size() < t2.size();
	}
};

typedef std::priority_queue<task, std::vector<task>, compare_by_size> prior_q;

void cycle(const std::vector<task> &tasks, const adj_list &graph,
           int last, std::vector<int> &parent_tasks, prior_q &task_queue)
{
	for (unsigned int i = 0; i < graph[last].size(); ++i) {
		int parents = --parent_tasks[graph[last][i]];
		if (parents == 0) {
			int id = tasks[graph[last][i]].get_id();
			task_queue.push(tasks[id]);
		}
	}
}

schedule ltf_schedule(const std::vector<task> &tasks, const adj_list &graph) {
	schedule ltf;
	std::vector<int> parent_tasks = parent_task_count(graph);
	prior_q task_queue;
	for (unsigned int i = 0; i < graph.size(); ++i) {
		if (parent_tasks[i] == 0) {
		// If there are no parent tasks
			task_queue.push(tasks[i]);
		}
	}
	double lp_time = 0.0, hp_time = 0.0;
	int last_lp = -1, last_hp = -1;
	while (! task_queue.empty()) {
		task T = task_queue.top();
		task_queue.pop();
		if (lp_time <= hp_time && (lp_time + T.lp_size() <= MAX_DUR)) {
			double size = T.lp_size();
			if (last_lp != -1) cycle(tasks, graph, last_lp, parent_tasks, task_queue);
			last_lp = T.get_id();
			ltf.add_LP_slot(last_lp, lp_time, size);
			lp_time += size;

			if (lp_time >= hp_time && last_hp != -1) {
				cycle(tasks, graph, last_hp, parent_tasks, task_queue);
				last_hp = -1;
			}
		} else {
			double size = T.size();
			if (last_hp != -1) cycle(tasks, graph, last_hp, parent_tasks, task_queue);
			last_hp = T.get_id();
			ltf.add_HP_slot(last_hp, hp_time, size);
			hp_time += size;

			if (hp_time >= lp_time && last_lp != -1) {
				cycle(tasks, graph, last_lp, parent_tasks, task_queue);
				last_lp = -1;
			}
		}

		if (task_queue.empty()) {
			lp_time = hp_time = std::max(lp_time, hp_time);
			if (last_lp != -1) {
				cycle(tasks, graph, last_lp, parent_tasks, task_queue);
				last_lp = -1;
			}
			if (last_hp != -1) {
				cycle(tasks, graph, last_hp, parent_tasks, task_queue);
				last_hp = -1;
			}
		}
	}
	return ltf;
}
