#include "task.hpp"

std::vector<edge> read_edges(std::ifstream &stream) {
	std::vector<edge> list_of_edges;
	int parent_node, child_node;
	while (stream >> parent_node >> child_node) {
		edge new_edge = { parent_node, child_node };
		list_of_edges.push_back(new_edge);
	}
	return list_of_edges;
}
