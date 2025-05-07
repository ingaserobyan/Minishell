/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctor.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:18 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:20 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_node	*make_node(void)
{
	t_node	*node;

	node = (t_node *) malloc(sizeof(t_node));
	if (!node)
	{
		set_unsigned_status(MALLOC_ERROR);
		return (NULL);
	}
	init_node(node);
	return (node);
}

t_tree	*make_tree(void)
{
	t_tree		*tree;

	tree = (t_tree *) malloc(sizeof(t_tree));
	if (!tree)
	{
		set_unsigned_status(MALLOC_ERROR);
		return (NULL);
	}
	init_tree(tree);
	if (!tree->nill && get_status() == MALLOC_ERROR)
	{
		free(tree);
		return (NULL);
	}
	return (tree);
}

t_list	*make_list(void)
{
	t_list	*list;

	list = (t_list *) malloc(sizeof(t_list));
	if (!list)
	{
		set_unsigned_status(MALLOC_ERROR);
		return (NULL);
	}
	init_list(list);
	return (list);
}

t_handler	*make_handler(void)
{
	t_handler	*handler;

	handler = (t_handler *) malloc(sizeof(t_handler));
	if (!handler)
	{
		set_unsigned_status(MALLOC_ERROR);
		return (NULL);
	}
	init_handler(handler);
	return (handler);
}
