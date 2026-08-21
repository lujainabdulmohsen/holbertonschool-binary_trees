#include <stdlib.h>
#include "binary_trees.h"

/**
 * free_heap - Frees a heap
 * @tree: Pointer to the root node
 */
static void free_heap(heap_t *tree)
{
	if (tree == NULL)
		return;

	free_heap(tree->left);
	free_heap(tree->right);
	free(tree);
}

/**
 * array_to_heap - Builds a Max Binary Heap from an array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root of the created heap, or NULL on failure
 */
heap_t *array_to_heap(int *array, size_t size)
{
	size_t i;
	heap_t *root;
	heap_t *node;

	if (array == NULL || size == 0)
		return (NULL);

	root = NULL;

	for (i = 0; i < size; i++)
	{
		node = heap_insert(&root, array[i]);
		if (node == NULL)
		{
			free_heap(root);
			return (NULL);
		}
	}

	return (root);
}
