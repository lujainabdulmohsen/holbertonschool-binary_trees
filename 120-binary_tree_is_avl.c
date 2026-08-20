#include "binary_trees.h"

/**
 * tree_height - Measures the height of a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Height of the tree
 */
static size_t tree_height(const binary_tree_t *tree)
{
	size_t left_height, right_height;

	if (tree == NULL)
		return (0);

	left_height = tree_height(tree->left);
	right_height = tree_height(tree->right);

	if (left_height > right_height)
		return (left_height + 1);

	return (right_height + 1);
}

/**
 * is_bst_range - Checks if a tree is a valid BST within a range
 * @tree: Pointer to the root node
 * @min: Minimum allowed value
 * @max: Maximum allowed value
 *
 * Return: 1 if valid BST, 0 otherwise
 */
static int is_bst_range(const binary_tree_t *tree, int min, int max)
{
	if (tree == NULL)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	return (is_bst_range(tree->left, min, tree->n) &&
		is_bst_range(tree->right, tree->n, max));
}

/**
 * is_balanced - Checks if every node is balanced
 * @tree: Pointer to the root node
 *
 * Return: 1 if balanced, 0 otherwise
 */
static int is_balanced(const binary_tree_t *tree)
{
	size_t left_height, right_height;

	if (tree == NULL)
		return (1);

	left_height = tree_height(tree->left);
	right_height = tree_height(tree->right);

	if (left_height > right_height + 1 ||
	    right_height > left_height + 1)
		return (0);

	return (is_balanced(tree->left) &&
		is_balanced(tree->right));
}

/**
 * binary_tree_is_avl - Checks if a binary tree is a valid AVL tree
 * @tree: Pointer to the root node
 *
 * Return: 1 if AVL, 0 otherwise
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	if (!is_bst_range(tree, -2147483648, 2147483647))
		return (0);

	return (is_balanced(tree));
}
