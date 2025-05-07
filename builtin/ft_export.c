/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:45:19 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:45:33 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

static void	update_existing_node(char **args, t_shell *shell,
	t_handler *handler, t_export_data	*f_data)
{
	f_data->node->temp_value = f_data->node->value;
	f_data->node->value = cut_after(args[f_data->i], SEPARATOR);
	if (get_status() == MALLOC_ERROR)
	{
		free(f_data->key);
		f_data->key = NULL;
		error_msg_env("Not enough memory\n", NULL, NULL, NULL);
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
	}
	if (f_data->node->value == NULL)
	{
		f_data->node->value = f_data->node->temp_value;
		f_data->node->temp_value = NULL;
	}
	else
	{
		if (f_data->node->temp_value == NULL)
			insert_to_list(f_data->node, handler->list);
		free(f_data->node->temp_value);
		f_data->node->temp_value = NULL;
	}
}

static int	get_key(char **args, char *exec_name,
	t_shell *shell, t_export_data	*f_data)
{
	t_handler	*handler;

	handler = shell->handler;
	f_data->key = cut_until(args[f_data->i], SEPARATOR);
	handle_malloc_error(shell);
	if (ft_strcmp_env(f_data->key, "_") == 0)
	{
		f_data->key = free_chr_ptr(f_data->key);
		(f_data->i)++;
		return (CONTINUE_WHILE);
	}
	if (!is_valid_identifier(f_data->key))
	{
		set_unsigned_status(1);
		error_msg_env(exec_name, args[0],
			args[f_data->i], "not a valid identifier");
		f_data->key = free_chr_ptr(f_data->key);
		(f_data->i)++;
		return (CONTINUE_WHILE);
	}
	return (0);
}

static int	iterate_export_args(char **args, char *exec_name,
	t_shell *shell, t_export_data	*f_data)
{
	t_handler	*handler;

	handler = shell->handler;
	while (args[f_data->i] != NULL)
	{
		if (get_key(args, exec_name, shell, f_data) == CONTINUE_WHILE)
			continue ;
		f_data->node = search_node(handler->tree, f_data->key);
		if (!nodes_are_same(f_data->node, handler->tree->nill))
			update_existing_node(args, shell, handler, f_data);
		else
		{
			f_data->node = new_nodes_from_env(args[f_data->i]);
			if (!f_data->node)
				return (-1);
			insert_to_tree(f_data->node, handler->tree);
			if (f_data->node->value != NULL)
				insert_to_list(f_data->node, handler->list);
		}
		f_data->key = free_chr_ptr(f_data->key);
		(f_data->i)++;
	}
	return (0);
}

int	ft_export(char **args, t_handler *handler, char *exec_name, t_shell *shell)
{
	t_export_data	f_data;

	init_export_data(&f_data);
	if (!args || !handler)
		return (0);
	if (ft_strcmp_env(args[f_data.i], "export") != 0)
		return (1);
	(f_data.i)++;
	set_unsigned_status(0);
	if (args[f_data.i] == NULL)
		print_tree_inorder(handler->tree, handler->tree->root);
	else
	{
		if (iterate_export_args(args, exec_name, shell, &f_data) == -1)
			return (-1);
	}
	return (0);
}
