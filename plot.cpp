#include <iostream>
#include <fstream>
#include <vector>
#include "task.hpp"
#include "adj_list.hpp"
#include "schedule.hpp"

int main(int argc, const char *argv[]) {
	if (argc <= 1) {
		std::cout << "usage: plot_data [LIST OF TASKS]" << std::endl;
		return 1;
	}

	std::ifstream task_data;
	std::ofstream plot_data("energy-plot", std::ios::out);
	for (int i = 1; i < argc; ++i) {
		task_data.open(argv[i], std::ios::in);
		if (! task_data.is_open()) {
			std::cerr << "Could not open task file!" << std::endl;
			continue;
		}
		std::cout << "Opened " << argv[i] << std::endl;
		std::cout << "Reading File...";
		std::vector<task> tasks = read_tasks(task_data);
		std::vector<edge> edges = read_edges(task_data);
		task_data.close();

		adj_list graph = list_from_edges(edges, tasks.size());
		std::cout << "done." << std::endl;

		std::cout << "Generating LTF...";
		schedule ltf = ltf_schedule(tasks, graph);
		std::cout << "done." << std::endl;
		plot_data << "";

		std::cout << "Generating LTF (contingency)...";
		schedule ltf_cs = contingency_schedule(ltf);
		std::cout << "done." << std::endl;

		std::cout << "Generating LTF-US...";
		schedule ltf_us = uniform_scale(ltf, ltf_cs);
		std::cout << "done." << std::endl;

		plot_data << ltf.utilization() << " " << ltf.energy() << " " << ltf_us.energy() << std::endl;
		task_data.close();
	}
	plot_data.close();
	return 0;
}
