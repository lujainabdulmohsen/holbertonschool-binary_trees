#include "binary_trees.h"

/**
 * heap_size - Gets the number of nodes in a heap.
 * @root: Pointer to the root node.
 *
 * Return: Number of nodes.
 */
static size_t heap_size(heap_t *root)
{
	size_t size;

	if (!root)
		return (0);

	size = 1;
	size += heap_size(root->left);
	size += heap_size(root->right);

	return (size);
}

/**
 * get_last_node - Gets the last node in level-order.
 * @root: Pointer to the root node.
 * @index: Index of the last node.
 *
 * Return: Pointer to the last node.
 */
static heap_t *get_last_node(heap_t *root, size_t index)
{
	size_t bit;
	heap_t *node;

	if (!root)
		return (NULL);

	node = root;
	bit = 1;

	while (bit <= index)
		bit <<= 1;

	bit >>= 2;

	while (bit)
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
 * sift_down - Restores the Max Heap property.
 * @root: Pointer to the root node.
 *
 * Return: Nothing.
 */
static void sift_down(heap_t *root)
{
	heap_t *largest;
	int temp;

	while (root)
	{
		largest = root;

		if (root->left && root->left->n > largest->n)
			largest = root->left;

		if (root->right && root->right->n > largest->n)
			largest = root->right;

		if (largest == root)
			break;

		temp = root->n;
		root->n = largest->n;
		largest->n = temp;

		root = largest;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap.
 * @root: Double pointer to the root node.
 *
 * Return: Value stored in the root node, or 0 on failure.
 */
int heap_extract(heap_t **root)
{
	heap_t *last;
	heap_t *old_root;
	size_t size;
	int value;

	if (!root || !*root)
		return (0);

	old_root = *root;
	value = old_root->n;

	size = heap_size(old_root);

	if (size == 1)
	{
		free(old_root);
		*root = NULL;
		return (value);
	}

	last = get_last_node(old_root, size);

	old_root->n = last->n;

	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;

	free(last);

	sift_down(old_root);

	return (value);
}
