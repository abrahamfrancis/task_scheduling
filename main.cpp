#include <iostream>
#include <fstream>
#include <vector>
#include "task.hpp"
#include "adj_list.hpp"
#include "schedule.hpp"

int main(int argc, const char *argv[]) {
	std::ifstream task_data;
	if (argc == 1) {
		task_data.open("task-graphs/example.tgff", std::ios::in);
	} else {
		task_data.open(argv[1], std::ios::in);
	}
	if (! task_data.is_open()) {
		std::cerr << "Could not open task file!" << std::endl;
		return 1;
	}
	std::vector<task> tasks = read_tasks(task_data);
	std::vector<edge> edges = read_edges(task_data);
	task_data.close();

	adj_list graph = list_from_edges(edges, tasks.size());

	schedule ltf = ltf_schedule(tasks, graph);
	std::ofstream ltf_sched("ltf-schedule", std::ios::out);
	ltf.show(ltf_sched);
	ltf_sched.close();

	ltf_sched.open("ltf-schedule-us", std::ios::out);
	ltf.uniform_scale().show(ltf_sched);
	ltf_sched.close();
	return 0;
}
