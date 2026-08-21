#include "binary_trees.h"

/**
 * array_to_avl - Builds an AVL tree from an array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root of the AVL tree, or NULL on failure
 */
avl_t *array_to_avl(int *array, size_t size)
{
	avl_t *tree;
	size_t i;

	if (array == NULL || size == 0)
		return (NULL);

	tree = NULL;

	for (i = 0; i < size; i++)
	{
		if (avl_insert(&tree, array[i]) == NULL)
		{
			/*
			 * NULL can mean either duplicate or allocation failure.
			 * Duplicates must simply be ignored.
			 */
			continue;
		}
	}

	return (tree);
}
