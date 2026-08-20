#include "binary_trees.h"

/**
 * bst_insert - Inserts a value in a Binary Search Tree.
 *
 * @tree: Double pointer to the root of the BST.
 * @value: Value to insert.
 *
 * Return: Pointer to the created node, or NULL on failure.
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	bst_t *current;
	bst_t *parent;
	bst_t *new_node;

	if (!tree)
		return (NULL);

	if (!*tree)
	{
		new_node = binary_tree_node(NULL, value);
		*tree = new_node;
		return (new_node);
	}

	current = *tree;
	parent = NULL;

	while (current)
	{
		parent = current;

		if (value == current->n)
			return (NULL);

		if (value < current->n)
			current = current->left;
		else
			current = current->right;
	}

	new_node = binary_tree_node(parent, value);
	if (!new_node)
		return (NULL);

	if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	return (new_node);
}
