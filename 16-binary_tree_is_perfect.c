#include "binary_trees.h"

/**
 * tree_depth - Finds the depth of the leftmost leaf
 * @tree: Pointer to the root node
 *
 * Return: Depth of the leftmost leaf
 */
static size_t tree_depth(const binary_tree_t *tree)
{
	size_t depth = 0;

	while (tree->left != NULL)
	{
		depth++;
		tree = tree->left;
	}

	return (depth);
}

/**
 * check_perfect - Checks if a binary tree is perfect
 * @tree: Pointer to the current node
 * @depth: Expected depth of leaves
 * @level: Current node level
 *
 * Return: 1 if perfect, otherwise 0
 */
static int check_perfect(const binary_tree_t *tree, size_t depth, size_t level)
{
	if (tree->left == NULL && tree->right == NULL)
		return (depth == level);

	if (tree->left == NULL || tree->right == NULL)
		return (0);

	return (check_perfect(tree->left, depth, level + 1) &&
		check_perfect(tree->right, depth, level + 1));
}

/**
 * binary_tree_is_perfect - Checks if a binary tree is perfect
 * @tree: Pointer to the root node of the tree
 *
 * Return: 1 if the tree is perfect, otherwise 0
 */
int binary_tree_is_perfect(const binary_tree_t *tree)
{
	size_t depth;

	if (tree == NULL)
		return (0);

	depth = tree_depth(tree);

	return (check_perfect(tree, depth, 0));
}
