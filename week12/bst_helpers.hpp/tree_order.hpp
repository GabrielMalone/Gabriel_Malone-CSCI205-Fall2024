#ifndef TREEORDER
#define TREEORDER

template <typename T>
struct tree_order {
	bool left = false;
	bool right = false;
	int position = 0;
	int level = 0;
	int value = -1;
	int parent_val = -1;
	int l_child_val = -1;
	int r_child_val = -1;
	bool has_left_child = false;
	bool has_right_child = false;
	A_TreeNode<T>* parent;
	bool operator==(const tree_order& other) const {
		return value == other.value; // Adjust this logic based on your class's members
	}
};

#endif