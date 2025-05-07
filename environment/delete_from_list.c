/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_from_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:31 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:54:33 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	delete_from_list(t_node *node, t_list *list)
{
	t_node	*next;
	t_node	*prev;

	if (!node || !list)
		return ;
	if (nodes_are_same(node, list->head))
		list->head = node->next;
	if (nodes_are_same(node, list->tail))
		list->tail = node->prev;
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	node->next = NULL;
	node->prev = NULL;
	if (!list->head)
		list->tail = NULL;
}

void	delete_handler(t_shell *shell)
{
	if (!shell || !shell->handler)
		return ;
	delete_tree(shell->handler->tree);
	delete_list_and_nodes(shell->handler->list);
	clear_handler(shell->handler);
	free(shell->handler);
	shell->handler = NULL;
}

t_handler	*delete_handler_ptr(t_handler **handler)
{
	if (!handler)
		return (NULL);
	delete_tree((*handler)->tree);
	delete_list_and_nodes((*handler)->list);
	clear_handler((*handler));
	free((*handler));
	(*handler) = NULL;
	return (*handler);
}
