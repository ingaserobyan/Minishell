/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:24 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 16:02:21 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_node	*free_node(t_node *node)
{
	if (!node)
		return (NULL);
	node->key = free_chr_ptr(node->key);
	node->value = free_chr_ptr(node->key);
	node->temp_value = free_chr_ptr(node->key);
	free(node);
	return (NULL);
}

void	clear_tree(t_tree *tree, t_node *node)
{
	int	delete;

	delete = FALSE;
	if (!tree)
		return ;
	if (nodes_are_same(tree->nill, node) == 0)
		return ;
	clear_tree(tree, node->left);
	clear_tree(tree, node->right);
	if (node->value == NULL)
		delete = TRUE;
	delete_from_tree(tree, node);
	if (delete)
		node = free_node(node);
}

void	delete_tree(t_tree *tree)
{
	if (!tree)
		return ;
	clear_tree(tree, tree->root);
	if (nodes_are_same(tree->root, tree->nill) == 0)
	{
		tree->root = NULL;
		tree->nill = free_node(tree->nill);
	}
}

void	delete_list_and_nodes(t_list *list)
{
	t_node	*next_node;
	t_node	*current_node;

	current_node = list->head;
	next_node = list->head;
	if (!list)
		return ;
	if (!list->head)
		return ;
	while (current_node)
	{
		next_node = current_node->next;
		delete_from_list(current_node, list);
		current_node = free_node(current_node);
		current_node = next_node;
	}
	list->head = NULL;
	list->tail = NULL;
}

void	clear_handler(t_handler *handler)
{
	if (!handler)
		return ;
	if (handler->tree)
	{
		free(handler->tree);
		handler->tree = NULL;
	}
	if (handler->list)
	{
		free(handler->list);
		handler->list = NULL;
	}
	handler->tmp = free_chr_ptr(handler->tmp);
	handler->exit_status = free_chr_ptr(handler->exit_status);
	handler->env = free_double_chr_ptr(handler->env);
}
