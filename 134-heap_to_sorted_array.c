#include <stdlib.h>
#include "binary_trees.h"

/**
 * heap_nodes - Counts the number of nodes in a heap.
 * @root: Pointer to the root node.
 *
 * Return: Number of nodes.
 */
static size_t heap_nodes(heap_t *root)
{
	if (!root)
		return (0);

	return (1 + heap_nodes(root->left) + heap_nodes(root->right));
}

/**
 * heap_to_sorted_array - Converts a Max Heap to a sorted array.
 * @heap: Pointer to the root node of the heap.
 * @size: Address to store the size of the array.
 *
 * Return: Pointer to the sorted array, or NULL on failure.
 */
int *heap_to_sorted_array(heap_t *heap, size_t *size)
{
	int *array;
	size_t i;
	size_t n;

	if (!heap)
	{
		*size = 0;
		return (NULL);
	}

	n = heap_nodes(heap);

	array = malloc(sizeof(int) * n);
	if (!array)
	{
		*size = 0;
		return (NULL);
	}

	i = 0;
	while (heap)
	{
		array[i] = heap_extract(&heap);
		i++;
	}

	*size = n;

	return (array);
}
