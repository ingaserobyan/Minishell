/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_env_to_ptr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:16 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:54:16 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	clear_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
}

void	set_status_and_exit(t_shell *shell, int status)
{
	set_unsigned_status(status);
	free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
}

void	allocate_chr_matrix(t_handler *handler, t_shell *shell)
{
	int	index;

	index = 0;
	handler->env = (char **) malloc(sizeof(char *)
			* (handler->list->nodes_count + 1));
	if (!handler->env)
		set_status_and_exit(shell, MALLOC_ERROR);
	while (index < handler->list->nodes_count)
	{
		handler->env[index] = NULL;
		index++;
	}
}

void	converter_env_to_ptr(t_handler *handler, t_shell *shell)
{
	t_node	*lst_tmp;
	int		index;

	lst_tmp = handler->list->head;
	index = 0;
	if (handler->env != NULL)
	{
		clear_env(handler->env);
		handler->env = free_double_chr_ptr(handler->env);
	}
	allocate_chr_matrix(handler, shell);
	while (lst_tmp)
	{
		handler->env[index] = ft_strjoin_ultra(lst_tmp->key, "=",
				lst_tmp->value);
		if (!handler->env[index])
		{
			handler->env = free_double_chr_ptr(handler->env);
			set_status_and_exit(shell, MALLOC_ERROR);
		}
		index++;
		lst_tmp = lst_tmp->next;
	}
	handler->env[index] = NULL;
}
