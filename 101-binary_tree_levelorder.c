#include "binary_trees.h"

/**
 * tree_height - Measures the height of a binary tree.
 *
 * @tree: Pointer to the root node.
 *
 * Return: Height of the tree.
 */
static size_t tree_height(const binary_tree_t *tree)
{
	size_t left_height, right_height;

	if (!tree)
		return (0);

	left_height = tree_height(tree->left);
	right_height = tree_height(tree->right);

	if (left_height > right_height)
		return (left_height + 1);

	return (right_height + 1);
}

/**
 * print_level - Prints all nodes at a given level.
 *
 * @tree: Pointer to the root node.
 * @level: Level to print.
 * @func: Function to call for each node.
 */
static void print_level(const binary_tree_t *tree, size_t level,
		void (*func)(int))
{
	if (!tree)
		return;

	if (level == 0)
	{
		func(tree->n);
		return;
	}

	print_level(tree->left, level - 1, func);
	print_level(tree->right, level - 1, func);
}

/**
 * binary_tree_levelorder - Goes through a binary tree using level-order.
 *
 * @tree: Pointer to the root node.
 * @func: Pointer to the function to call for each node.
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	size_t height, level;

	if (!tree || !func)
		return;

	height = tree_height(tree);

	for (level = 0; level < height; level++)
		print_level(tree, level, func);
}
