#include "task.hpp"

std::vector<edge> read_edges(std::ifstream &stream) {
	std::vector<edge> list_of_edges;
	int count;
	stream >> count;
	int parent_node, child_node;
	while (count--) {
		stream >> parent_node >> child_node;
		edge new_edge = { parent_node, child_node };
		list_of_edges.push_back(new_edge);
	}
	return list_of_edges;
}
