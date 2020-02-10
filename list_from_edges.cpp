#include "adj_list.hpp"

adj_list list_from_edges(const std::vector< std::pair<int, int> > &edges, int max_nodes) {
	adj_list alist = adj_list(max_nodes);
	for (auto &edge : edges) {
		alist[edge.first].push_back(edge.second);
	}
	return alist;
}
