/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:45:52 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:46:20 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	deleting_and_iterating(t_handler *handler, t_node *node, int i)
{
	if ((node->value) != NULL)
		delete_from_list(node, handler->list);
	i++;
	delete_from_tree(handler->tree, node);
	node->value = free_chr_ptr(node->value);
	node->key = free_chr_ptr(node->key);
	node->temp_value = free_chr_ptr(node->temp_value);
	free(node);
	return (i);
}

int	ft_unset(char **args, t_handler *handler, char *e_name, int i)
{
	t_node	*node;

	node = NULL;
	if (!args || !handler)
		return (-1);
	if (ft_strcmp_env(args[0], "unset") != 0)
		return (1);
	set_unsigned_status(0);
	while (args[i] != NULL)
	{
		if (!is_valid_identifier(args[i]))
		{
			set_unsigned_status(1);
			error_msg_env(e_name, args[0], args[i++], "not a valid identifier");
			continue ;
		}
		node = search_node(handler->tree, args[i]);
		if (nodes_are_same(node, handler->tree->nill))
		{
			i++;
			continue ;
		}
		i = deleting_and_iterating(handler, node, i);
	}
	return (0);
}
