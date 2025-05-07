/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:33:23 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:33:31 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	if_red_append(t_command **tmp_word, t_token **tmp_token, t_shell *shell)
{
	if ((*tmp_word)->red_out != NULL)
	{
		free((*tmp_word)->red_out);
		(*tmp_word)->red_out = NULL;
	}
	(*tmp_word)->red_append = ft_strdup((*tmp_token)->value);
	if (!(*tmp_word)->red_append)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	(*tmp_word)->fd_out = open((*tmp_word)->red_append, O_WRONLY
			| O_CREAT | O_APPEND, 0664);
	if ((*tmp_word)->fd_out < 0)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		perror((*tmp_word)->red_append);
		set_unsigned_status(PERMISSION_DENIED);
		(*tmp_word)->error_flag = -1;
	}
}

int	redirection_append(t_command **tmp_word,
t_token **tmp_token, t_shell *shell)
{
	if ((*tmp_token)->next)
	{
		(*tmp_token) = (*tmp_token)->next;
		if ((*tmp_token)->next && ((*tmp_token)->type == 8
				|| ft_strcmp((*tmp_token)->value, "") == 0))
			(*tmp_token) = (*tmp_token)->next;
		if (is_redir((*tmp_token)->value, shell))
			return (-1);
		if ((*tmp_token)->next && (*tmp_token)->type == 8)
			(*tmp_token) = (*tmp_token)->next;
		if ((*tmp_token)->type != 8)
		{
			if_red_append (tmp_word, tmp_token, shell);
			if ((*tmp_word)->error_flag == -1)
				return (0);
		}
	}
	if ((!(*tmp_word)->red_append))
	{
		set_unsigned_status(SYNTAX_ERROR);
		return (error_message
			("minishell: syntax error near unexpected token `newline'\n",
				NULL, NULL), -1);
	}
	return (0);
}
