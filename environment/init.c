/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:07 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:09 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	init_node(t_node *node)
{
	if (!node)
		return ;
	node->key = NULL;
	node->value = NULL;
	node->temp_value = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->color = RED;
	node->next = NULL;
	node->prev = NULL;
}

void	init_tree(t_tree *tree)
{
	if (!tree)
		return ;
	tree->nill = make_node();
	if (!tree->nill && get_status() == MALLOC_ERROR)
		return ;
	init_node(tree->nill);
	set_color_black(tree->nill);
	tree->root = tree->nill;
	tree->nodes_count = 0;
	tree->height = 0;
}

void	init_list(t_list *list)
{
	if (!list)
		return ;
	list->head = NULL;
	list->tail = NULL;
	list->nodes_count = 0;
}

void	init_handler(t_handler *handler)
{
	if (!handler)
		return ;
	handler->tree = NULL;
	handler->list = NULL;
	handler->env = NULL;
	handler->i = 0;
	handler->nodes_count = 0;
	handler->lst_cmd = NULL;
	handler->tmp = NULL;
	handler->exit_status = NULL;
}
