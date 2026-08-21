#include "binary_trees.h"

/**
 * tree_size - Counts the nodes in a binary tree
 *
 * @tree: Pointer to the root node
 *
 * Return: Number of nodes
 */
static size_t tree_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * is_heap - Checks if a binary tree is a valid Max Heap
 *
 * @tree: Pointer to the current node
 * @index: Index of the current node
 * @size: Number of nodes
 *
 * Return: 1 if valid, 0 otherwise
 */
static int is_heap(const binary_tree_t *tree, size_t index, size_t size)
{
	if (tree == NULL)
		return (1);

	if (index >= size)
		return (0);

	if (tree->left != NULL && tree->left->n > tree->n)
		return (0);

	if (tree->right != NULL && tree->right->n > tree->n)
		return (0);

	return (is_heap(tree->left, 2 * index + 1, size)
		&& is_heap(tree->right, 2 * index + 2, size));
}

/**
 * binary_tree_is_heap - Checks if a binary tree is a valid Max Heap
 *
 * @tree: Pointer to the root node
 *
 * Return: 1 if valid, 0 otherwise
 */
int binary_tree_is_heap(const binary_tree_t *tree)
{
	size_t size;

	if (tree == NULL)
		return (0);

	size = tree_size(tree);

	return (is_heap(tree, 0, size));
}
