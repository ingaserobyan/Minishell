/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:38:41 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:38:44 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	if_struct_init(t_command **tmp_word,
t_token **tmp_token, int *i, t_shell *shell)
{
	if (if_srct_init_is(tmp_token) == 1)
	{
		(*tmp_word)->args[*i] = ft_strdup((*tmp_token)->value);
		if (!(*tmp_word)->args[*i])
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		(*i)++;
		(*tmp_word)->args[*i] = NULL;
	}
	else if ((*tmp_token)->type == 3 || (*tmp_token)->type == 2
		|| (*tmp_token)->type == 4 || (*tmp_token)->type == 5)
	{
		if (redirection_init(tmp_word, tmp_token, shell) == -1)
			return (-1);
	}
	return (0);
}

int	struct_init(t_command **tmp_word,
t_token **tmp_token, int *i, t_shell *shell)
{
	while ((*tmp_token) && ft_strcmp((*tmp_token)->value, "|") != 0)
	{
		if (get_status() == SIGNAL_STATUS)
			break ;
		if (if_cmd_srct_init_is(tmp_token, tmp_word) == 1)
		{
			(*tmp_word)->command = ft_strdup((*tmp_token)->value);
			if (!(*tmp_word)->command)
				free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
			(*tmp_word)->type_command = (*tmp_token)->type;
		}
		if (if_struct_init(tmp_word, tmp_token, i, shell) == -1)
			return (-1);
		if ((*tmp_token)->next && (*tmp_token)->type != 1)
			(*tmp_token) = (*tmp_token)->next;
		else
			break ;
	}
	if ((*tmp_word)->command == NULL)
		(*tmp_word)->exist_cmd = -1;
	return (0);
}
