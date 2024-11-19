#ifndef CELL
#define CELL

#include "tree_order.hpp"

template <typename T>
struct Cell{
	int x_coord = 0;
	int y_coord = 0;
	tree_order<T> node_data;
	bool used = false;
	bool is_node = false;
	bool is_parent = false;
	bool is_connector = false;
};

#endif