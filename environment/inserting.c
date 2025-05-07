/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inserting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:13 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:14 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	insert_to_list(t_node	*new_node, t_list *list)
{
	if (!new_node || !list)
		return ;
	if (!list->head)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		new_node->prev = list->tail;
		list->tail = new_node;
	}
	list->nodes_count++;
}

void	insert_to_tree(t_node *new_node, t_tree *tree)
{
	if (!new_node || !tree)
		return ;
	tree_insert_helper(new_node, tree);
}

t_node	*new_node_k_v(char *key, char *value)
{
	t_node	*node;

	node = make_node();
	if (!node)
		return (NULL);
	node->key = ft_strdup_env(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (value)
	{
		node->value = ft_strdup_env(value);
		if (!node->value)
		{
			free(node->key);
			free(node);
			return (NULL);
		}
	}
	return (node);
}
