#include <iostream>
#include <fstream>
#include <vector>
#include "task.hpp"
#include "adj_list.hpp"
#include "schedule.hpp"

int main(int argc, const char *argv[]) {
	std::ifstream task_params("task_data/parameters", std::ios::in);
	std::ifstream task_preced("task_data/precedence", std::ios::in);
	std::vector<task> tasks = read_tasks(task_params);
	std::vector<edge> edges = read_edges(task_preced);
	task_params.close();
	task_preced.close();

	for (auto t : tasks) t.show();

	adj_list graph = list_from_edges(edges, tasks.size());

	schedule ltf = ltf_schedule(tasks, graph);
	std::ofstream ltf_sched("ltf-schedule", std::ios::out);
	ltf.show(ltf_sched);
	return 0;
}
