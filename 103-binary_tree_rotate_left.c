#include "binary_trees.h"

/**
 * binary_tree_rotate_left - Rotates a binary tree to the left.
 *
 * @tree: Pointer to the root node of the tree.
 *
 * Return: Pointer to the new root node.
 */
binary_tree_t *binary_tree_rotate_left(binary_tree_t *tree)
{
	binary_tree_t *right;
	binary_tree_t *parent;

	if (!tree || !tree->right)
		return (tree);

	right = tree->right;
	parent = tree->parent;

	tree->right = right->left;

	if (right->left)
		right->left->parent = tree;

	right->left = tree;
	tree->parent = right;

	right->parent = parent;

	if (parent)
	{
		if (parent->left == tree)
			parent->left = right;
		else
			parent->right = right;
	}

	return (right);
}
