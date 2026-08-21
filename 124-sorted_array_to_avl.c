#include <stddef.h>
#include "binary_trees.h"

/**
 * build_avl - Builds an AVL tree from a sorted array
 * @array: Pointer to the array
 * @start: Start index
 * @end: End index
 * @parent: Parent node
 *
 * Return: Pointer to the root of the subtree
 */
static avl_t *build_avl(int *array, int start, int end, avl_t *parent)
{
	int mid;
	avl_t *node;

	if (start > end)
		return (NULL);

	mid = start + (end - start) / 2;

	node = binary_tree_node(parent, array[mid]);
	if (node == NULL)
		return (NULL);

	node->left = build_avl(array, start, mid - 1, node);
	node->right = build_avl(array, mid + 1, end, node);

	return (node);
}

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root of the created AVL tree
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (array == NULL || size == 0)
		return (NULL);

	return (build_avl(array, 0, (int)size - 1, NULL));
}
