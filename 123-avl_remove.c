#include <stdlib.h>
#include "binary_trees.h"

/**
 * avl_min - Finds the smallest node in a subtree
 * @tree: Pointer to the subtree
 *
 * Return: Pointer to the smallest node
 */
static avl_t *avl_min(avl_t *tree)
{
	while (tree->left)
		tree = tree->left;

	return (tree);
}

/**
 * avl_rotate - Rebalances an AVL node
 * @node: Pointer to the node
 *
 * Return: New root of the subtree
 */
static avl_t *avl_rotate(avl_t *node)
{
	int balance;

	balance = binary_tree_balance(node);

	if (balance > 1)
	{
		if (binary_tree_balance(node->left) < 0)
			node->left = binary_tree_rotate_left(node->left);

		return (binary_tree_rotate_right(node));
	}

	if (balance < -1)
	{
		if (binary_tree_balance(node->right) > 0)
			node->right = binary_tree_rotate_right(node->right);

		return (binary_tree_rotate_left(node));
	}

	return (node);
}

/**
 * avl_delete - Deletes a node from an AVL tree
 * @node: Node to delete
 *
 * Return: Replacement node
 */
static avl_t *avl_delete(avl_t *node)
{
	avl_t *child;

	if (node->left == NULL)
	{
		child = node->right;
		if (child)
			child->parent = node->parent;
		free(node);
		return (child);
	}

	if (node->right == NULL)
	{
		child = node->left;
		child->parent = node->parent;
		free(node);
		return (child);
	}

	return (node);
}

/**
 * avl_remove_node - Removes a value and rebalances the subtree
 * @root: Root of the subtree
 * @value: Value to remove
 *
 * Return: New root of the subtree
 */
static avl_t *avl_remove_node(avl_t *root, int value)
{
	avl_t *successor;

	if (root == NULL)
		return (NULL);

	if (value < root->n)
	{
		root->left = avl_remove_node(root->left, value);
		if (root->left)
			root->left->parent = root;
	}
	else if (value > root->n)
	{
		root->right = avl_remove_node(root->right, value);
		if (root->right)
			root->right->parent = root;
	}
	else
	{
		if (root->left && root->right)
		{
			successor = avl_min(root->right);
			root->n = successor->n;
			root->right = avl_remove_node(root->right, successor->n);

			if (root->right)
				root->right->parent = root;
		}
		else
		{
			root = avl_delete(root);

			if (root == NULL)
				return (NULL);
		}
	}

	return (avl_rotate(root));
}

/**
 * avl_remove - Removes a value from an AVL tree
 * @root: Root of the AVL tree
 * @value: Value to remove
 *
 * Return: New root of the AVL tree
 */
avl_t *avl_remove(avl_t *root, int value)
{
	root = avl_remove_node(root, value);

	if (root)
		root->parent = NULL;

	return (root);
}
