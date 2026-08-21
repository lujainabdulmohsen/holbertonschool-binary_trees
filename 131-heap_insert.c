#include <stdlib.h>
#include "binary_trees.h"

/**
 * heap_size - Counts the nodes in a binary heap
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
 * heap_parent - Finds the parent of the next node
 * @root: Pointer to the root
 * @index: Index of the new node
 *
 * Return: Pointer to the parent node
 */
static heap_t *heap_parent(heap_t *root, size_t index)
{
	size_t bit;
	heap_t *parent;

	parent = root;
	bit = 1;

	while (bit <= index / 2)
		bit <<= 1;

	bit >>= 2;

	while (bit != 0)
	{
		if (index & bit)
			parent = parent->right;
		else
			parent = parent->left;
		bit >>= 1;
	}

	return (parent);
}

/**
 * heap_bubble_up - Restores the Max Heap property
 * @node: Pointer to the inserted node
 *
 * Return: Pointer to the final position of the inserted node
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
 * @root: Double pointer to the root of the heap
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
	parent = heap_parent(*root, index);

	node->parent = parent;

	if ((index & 1) == 0)
		parent->left = node;
	else
		parent->right = node;

	return (heap_bubble_up(node));
}
