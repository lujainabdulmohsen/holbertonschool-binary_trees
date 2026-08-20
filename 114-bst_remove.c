#include <stdlib.h>
#include "binary_trees.h"

/**
 * find_successor - Finds the smallest node in a subtree
 * @tree: Root of the subtree
 *
 * Return: Pointer to the smallest node
 */
static bst_t *find_successor(bst_t *tree)
{
	while (tree->left)
		tree = tree->left;

	return (tree);
}

/**
 * remove_node - Removes a node with one or no children
 * @root: Root of the tree
 * @node: Node to remove
 *
 * Return: New root of the tree
 */
static bst_t *remove_node(bst_t *root, bst_t *node)
{
	bst_t *parent;
	bst_t *child;

	parent = node->parent;
	child = node->left ? node->left : node->right;

	if (!parent)
	{
		if (child)
			child->parent = NULL;
		free(node);
		return (child);
	}

	if (parent->left == node)
		parent->left = child;
	else
		parent->right = child;

	if (child)
		child->parent = parent;

	free(node);
	return (root);
}

/**
 * remove_two_children - Removes a node with two children
 * @root: Root of the tree
 * @node: Node to remove
 *
 * Return: Root of the tree
 */
static bst_t *remove_two_children(bst_t *root, bst_t *node)
{
	bst_t *successor;
	bst_t *child;
	bst_t *parent;

	successor = find_successor(node->right);
	node->n = successor->n;

	parent = successor->parent;
	child = successor->right;

	if (parent->left == successor)
		parent->left = child;
	else
		parent->right = child;

	if (child)
		child->parent = parent;

	free(successor);
	return (root);
}

/**
 * bst_remove - Removes a node from a Binary Search Tree
 * @root: Pointer to the root node
 * @value: Value to remove
 *
 * Return: Pointer to the new root
 */
bst_t *bst_remove(bst_t *root, int value)
{
	bst_t *node;

	node = root;

	while (node)
	{
		if (value == node->n)
			break;

		if (value < node->n)
			node = node->left;
		else
			node = node->right;
	}

	if (!node)
		return (root);

	if (node->left && node->right)
		return (remove_two_children(root, node));

	return (remove_node(root, node));
}
