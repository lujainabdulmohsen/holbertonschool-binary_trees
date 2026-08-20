#include <stdlib.h>
#include "binary_trees.h"

/**
 * queue_free - Frees a queue.
 *
 * @queue: Pointer to the queue.
 */
static void queue_free(queue_node_t *queue)
{
	queue_node_t *tmp;

	while (queue)
	{
		tmp = queue;
		queue = queue->next;
		free(tmp);
	}
}

/**
 * queue_add - Adds a node to the queue.
 *
 * @front: Pointer to the first queue node.
 * @back: Pointer to the last queue node.
 * @tree: Pointer to the tree node.
 *
 * Return: 0 on success, 1 on failure.
 */
static int queue_add(queue_node_t **front, queue_node_t **back,
		const binary_tree_t *tree)
{
	queue_node_t *new_node;

	new_node = malloc(sizeof(queue_node_t));
	if (!new_node)
		return (1);

	new_node->tree = tree;
	new_node->next = NULL;

	if (*back)
		(*back)->next = new_node;
	else
		*front = new_node;

	*back = new_node;

	return (0);
}

/**
 * queue_children - Adds the children of a node to the queue.
 *
 * @node: Current tree node.
 * @front: Pointer to the first queue node.
 * @back: Pointer to the last queue node.
 *
 * Return: 0 on success, 1 on failure.
 */
static int queue_children(const binary_tree_t *node,
		queue_node_t **front, queue_node_t **back)
{
	if (node->left &&
		queue_add(front, back, node->left))
		return (1);

	if (node->right &&
		queue_add(front, back, node->right))
		return (1);

	return (0);
}

/**
 * binary_tree_levelorder - Goes through a binary tree using level-order.
 *
 * @tree: Pointer to the root node.
 * @func: Pointer to the function to call for each node.
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	queue_node_t *front, *back, *current;

	if (!tree || !func)
		return;

	front = NULL;
	back = NULL;

	if (queue_add(&front, &back, tree))
		return;

	while (front)
	{
		current = front;
		front = front->next;

		func(current->tree->n);

		if (queue_children(current->tree, &front, &back))
		{
			free(current);
			queue_free(front);
			return;
		}

		if (!front)
			back = NULL;

		free(current);
	}
}
