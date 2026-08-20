#include "binary_trees.h"

/**
 * array_to_bst - Builds a BST from an array.
 *
 * @array: Pointer to the first element of the array.
 * @size: Number of elements in the array.
 *
 * Return: Pointer to the root node, or NULL on failure.
 */
bst_t *array_to_bst(int *array, size_t size)
{
	bst_t *tree;
	size_t i;

	if (!array || size == 0)
		return (NULL);

	tree = NULL;

	for (i = 0; i < size; i++)
		bst_insert(&tree, array[i]);

	return (tree);
}
