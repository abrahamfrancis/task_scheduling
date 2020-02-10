#ifndef _ADJ_LIST_

#define _ADJ_LIST_

#include <vector>

typedef std::vector< std::vector<int> > adj_list;

adj_list list_from_edges(const std::vector< std::pair<int, int> > &, int);

#endif
