#include "binary_search_tree.h"

void insert_value(node_t **tree, int value) {
	if (*tree == NULL) {
		*tree = calloc(1, sizeof(node_t));
		(*tree)->data = value;
	} else if (value <= (*tree)->data) {
		insert_value(&((*tree)->left), value);
	} else if (value > (*tree)->data) {
		insert_value(&((*tree)->right), value);
	}
}

node_t *build_tree(int *tree_data, size_t tree_data_len) {
	node_t *tree = NULL;

	for (size_t i = 0; i < tree_data_len; i++) {
		insert_value(&tree, tree_data[i]);	
	}

	return tree;
}

void free_tree(node_t *tree) {
	if (tree) {
		free_tree(tree->left);
		free_tree(tree->right);
		free(tree);
	}
}

int get_data(int **sorted, node_t *tree) {
	int left_len, right_len, *left_data = NULL, *right_data = NULL;

	if (tree == NULL) {
		return 0;
	}

	left_len = get_data(&left_data, tree->left);
	right_len = get_data(&right_data, tree->right);

	*sorted = malloc((left_len + right_len + 1) * sizeof(int));
	for (int i = 0; i < left_len; i++) {
		(*sorted)[i] = left_data[i];
	}
	(*sorted)[left_len] = tree->data;
	for (int i = 0; i < right_len; i++) {
		(*sorted)[left_len + 1 + i] = right_data[i];
	}

	free(left_data);
	free(right_data);

	return left_len + 1 + right_len;
}

int *sorted_data(node_t *tree) {
	int *sorted = NULL;

	get_data(&sorted, tree);

	return sorted;
}