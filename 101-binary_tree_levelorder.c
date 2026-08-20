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
 * @back: Pointer to the last node in the queue.
 * @tree: Pointer to the tree node.
 *
 * Return: New queue node, or NULL on failure.
 */
static queue_node_t *queue_add(queue_node_t **back,
		const binary_tree_t *tree)
{
	queue_node_t *new_node;

	new_node = malloc(sizeof(queue_node_t));
	if (!new_node)
		return (NULL);

	new_node->tree = tree;
	new_node->next = NULL;

	if (*back)
		(*back)->next = new_node;

	*back = new_node;
	return (new_node);
}

/**
 * queue_children - Adds the children of a node to the queue.
 *
 * @node: Current queue node.
 * @back: Pointer to the last queue node.
 *
 * Return: 0 on success, 1 on failure.
 */
static int queue_children(queue_node_t *node, queue_node_t **back)
{
	queue_node_t *new_node;

	if (node->tree->left)
	{
		new_node = queue_add(back, node->tree->left);
		if (!new_node)
			return (1);
	}

	if (node->tree->right)
	{
		new_node = queue_add(back, node->tree->right);
		if (!new_node)
			return (1);
	}

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

	back = NULL;
	front = queue_add(&back, tree);

	while (front)
	{
		current = front;
		front = front->next;

		func(current->tree->n);

		if (queue_children(current, &back))
		{
			free(current);
			queue_free(front);
			return;
		}

		if (current == back)
			back = NULL;

		free(current);
	}
}
