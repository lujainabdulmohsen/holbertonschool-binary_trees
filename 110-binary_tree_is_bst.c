#include "binary_trees.h"
#include <limits.h>

/**
 * check_bst - Checks if a binary tree is a valid BST.
 *
 * @tree: Pointer to the current node.
 * @min: Minimum allowed value.
 * @max: Maximum allowed value.
 *
 * Return: 1 if valid BST, 0 otherwise.
 */
static int check_bst(const binary_tree_t *tree, long min, long max)
{
	if (!tree)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	if (!check_bst(tree->left, min, tree->n))
		return (0);

	return (check_bst(tree->right, tree->n, max));
}

/**
 * binary_tree_is_bst - Checks if a binary tree is a valid BST.
 *
 * @tree: Pointer to the root node.
 *
 * Return: 1 if valid BST, 0 otherwise.
 */
int binary_tree_is_bst(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (check_bst(tree, LONG_MIN, LONG_MAX));
}
