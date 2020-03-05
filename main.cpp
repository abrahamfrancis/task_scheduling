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
	std::cout << "Reading File...";
	std::vector<task> tasks = read_tasks(task_data);
	std::vector<edge> edges = read_edges(task_data);
	task_data.close();

	adj_list graph = list_from_edges(edges, tasks.size());
	std::cout << "done." << std::endl;

	std::cout << "Generating LTF...";
	schedule ltf = ltf_schedule(tasks, graph);
	std::ofstream ltf_sched("ltf-schedule", std::ios::out);
	ltf.show(ltf_sched);
	ltf_sched.close();
	std::cout << "done." << std::endl;

	std::cout << "Generating LTF (contingency)...";
	schedule ltf_cs = contingency_schedule(ltf);
	ltf_sched.open("ltf-schedule-cs", std::ios::out);
	ltf_cs.show(ltf_sched);
	ltf_sched.close();
	std::cout << "done." << std::endl;

	std::cout << "Generating LTF-US...";
	schedule ltf_us = uniform_scale(ltf, ltf_cs);
	ltf_sched.open("ltf-schedule-us", std::ios::out);
	ltf_us.show(ltf_sched);
	ltf_sched.close();
	std::cout << "done." << std::endl;

	std::cout << "Generating TBLS...";
	schedule tbls = tbls_schedule(tasks, graph);
	std::ofstream tbls_sched("tbls-schedule", std::ios::out);
	tbls.show(tbls_sched);
	tbls_sched.close();
	std::cout << "done." << std::endl;

	std::cout << "Generating TBLS (contingency)...";
	schedule tbls_cs = contingency_schedule(tbls);
	tbls_sched.open("tbls-schedule-cs", std::ios::out);
	tbls_cs.show(tbls_sched);
	tbls_sched.close();
	std::cout << "done." << std::endl;

	std::cout << "Generating TBLS-US...";
	schedule tbls_us = uniform_scale(tbls, tbls_cs);
	tbls_sched.open("tbls-schedule-us", std::ios::out);
	tbls_us.show(tbls_sched);
	tbls_sched.close();
	std::cout << "done." << std::endl;
	return 0;
}
