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
 * @front: Pointer to the front of the queue.
 * @back: Pointer to the back of the queue.
 * @tree: Tree node to add.
 *
 * Return: 1 on success, 0 on failure.
 */
static int queue_add(queue_node_t **front, queue_node_t **back,
		const binary_tree_t *tree)
{
	queue_node_t *new_node;

	new_node = malloc(sizeof(queue_node_t));
	if (!new_node)
		return (0);

	new_node->tree = tree;
	new_node->next = NULL;

	if (*back)
		(*back)->next = new_node;
	else
		*front = new_node;

	*back = new_node;

	return (1);
}

/**
 * check_children - Checks and adds a node's children.
 *
 * @node: Current tree node.
 * @front: Pointer to the front of the queue.
 * @back: Pointer to the back of the queue.
 * @gap: Indicates that a missing child was found.
 *
 * Return: 1 if valid, 0 otherwise.
 */
static int check_children(const binary_tree_t *node,
		queue_node_t **front, queue_node_t **back, int *gap)
{
	if (!node->left)
		*gap = 1;
	else
	{
		if (*gap || !queue_add(front, back, node->left))
			return (0);
	}

	if (!node->right)
		*gap = 1;
	else
	{
		if (*gap || !queue_add(front, back, node->right))
			return (0);
	}

	return (1);
}

/**
 * binary_tree_is_complete - Checks if a binary tree is complete.
 *
 * @tree: Pointer to the root node.
 *
 * Return: 1 if the tree is complete, 0 otherwise.
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	queue_node_t *front, *back, *current;
	int gap;

	if (!tree)
		return (0);

	front = NULL;
	back = NULL;
	gap = 0;

	if (!queue_add(&front, &back, tree))
		return (0);

	while (front)
	{
		current = front;
		front = front->next;

		if (!check_children(current->tree, &front, &back, &gap))
		{
			free(current);
			queue_free(front);
			return (0);
		}

		free(current);
	}

	return (1);
}
