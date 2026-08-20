#include "binary_trees.h"

/**
 * binary_tree_count - Counts the nodes in a binary tree.
 *
 * @tree: Pointer to the root node.
 *
 * Return: Number of nodes.
 */
static size_t binary_tree_count(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + binary_tree_count(tree->left)
		+ binary_tree_count(tree->right));
}

/**
 * check_complete - Checks the indexes of a binary tree.
 *
 * @tree: Pointer to the root node.
 * @index: Index of the current node.
 * @count: Number of nodes in the tree.
 *
 * Return: 1 if valid, 0 otherwise.
 */
static int check_complete(const binary_tree_t *tree,
		size_t index, size_t count)
{
	if (!tree)
		return (1);

	if (index >= count)
		return (0);

	if (!check_complete(tree->left, 2 * index + 1, count))
		return (0);

	return (check_complete(tree->right, 2 * index + 2, count));
}

/**
 * binary_tree_is_complete - Checks if a binary tree is complete.
 *
 * @tree: Pointer to the root node.
 *
 * Return: 1 if complete, 0 otherwise.
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	size_t count;

	if (!tree)
		return (0);

	count = binary_tree_count(tree);

	return (check_complete(tree, 0, count));
}
