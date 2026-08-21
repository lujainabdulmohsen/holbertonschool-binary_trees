#include <stdlib.h>
#include "binary_trees.h"

/**
 * heap_size - Counts the number of nodes in a heap
 * @tree: Pointer to the root node
 *
 * Return: Number of nodes
 */
static size_t heap_size(const heap_t *tree)
{
	if (tree == NULL)
		return (0);

	return (1 + heap_size(tree->left) + heap_size(tree->right));
}

/**
 * heap_get_node - Gets a node using its heap index
 * @root: Pointer to the root node
 * @index: Index of the node
 *
 * Return: Pointer to the node
 */
static heap_t *heap_get_node(heap_t *root, size_t index)
{
	size_t bit;
	heap_t *node;

	node = root;
	bit = 1;

	while (bit <= index)
		bit <<= 1;

	bit >>= 2;

	while (bit != 0 && node != NULL)
	{
		if (index & bit)
			node = node->right;
		else
			node = node->left;

		bit >>= 1;
	}

	return (node);
}

/**
 * heap_bubble_up - Restores the Max Heap property
 * @node: Pointer to the inserted node
 *
 * Return: Pointer to the node
 */
static heap_t *heap_bubble_up(heap_t *node)
{
	heap_t *parent;
	int temp;

	while (node->parent != NULL && node->n > node->parent->n)
	{
		parent = node->parent;

		temp = node->n;
		node->n = parent->n;
		parent->n = temp;

		node = parent;
	}

	return (node);
}

/**
 * heap_insert - Inserts a value in a Max Binary Heap
 * @root: Double pointer to the root
 * @value: Value to insert
 *
 * Return: Pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *node;
	heap_t *parent;
	size_t index;

	if (root == NULL)
		return (NULL);

	node = binary_tree_node(NULL, value);
	if (node == NULL)
		return (NULL);

	if (*root == NULL)
	{
		*root = node;
		return (node);
	}

	index = heap_size(*root) + 1;
	parent = heap_get_node(*root, index / 2);

	if (index % 2 == 0)
		parent->left = node;
	else
		parent->right = node;

	node->parent = parent;

	return (heap_bubble_up(node));
}
