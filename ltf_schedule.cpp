#include "schedule.hpp"
#include "task.hpp"

schedule ltf_schedule(const std::vector<task> &tasks, const adj_list &graph) {
	schedule ltf = tbls_schedule(tasks, graph, 0.0);
	return ltf;
}
