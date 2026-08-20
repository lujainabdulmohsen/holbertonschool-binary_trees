#include "binary_trees.h"

/**
 * tree_depth - Measures the depth of a node.
 *
 * @node: Pointer to the node.
 *
 * Return: Depth of the node.
 */
static size_t tree_depth(const binary_tree_t *node)
{
	size_t depth = 0;

	while (node->parent)
	{
		depth++;
		node = node->parent;
	}

	return (depth);
}

/**
 * binary_trees_ancestor - Finds the lowest common ancestor of two nodes.
 *
 * @first: Pointer to the first node.
 * @second: Pointer to the second node.
 *
 * Return: Pointer to the lowest common ancestor, or NULL.
 */
binary_tree_t *binary_trees_ancestor(const binary_tree_t *first,
		const binary_tree_t *second)
{
	size_t depth_first, depth_second;

	if (!first || !second)
		return (NULL);

	depth_first = tree_depth(first);
	depth_second = tree_depth(second);

	while (depth_first > depth_second)
	{
		first = first->parent;
		depth_first--;
	}

	while (depth_second > depth_first)
	{
		second = second->parent;
		depth_second--;
	}

	while (first != second)
	{
		first = first->parent;
		second = second->parent;
	}

	return ((binary_tree_t *)first);
}
