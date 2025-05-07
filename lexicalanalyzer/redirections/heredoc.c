/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:33:03 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:33:11 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	if_token_next(t_token **tmp_token)
{
	if ((*tmp_token)->next)
		(*tmp_token) = (*tmp_token)->next;
}

void	if_heredoc(t_command **tmp_word, t_token **tmp_token, t_shell *shell)
{
	(*tmp_word)->heredoc = ft_strdup((*tmp_token)->value);
	if (!(*tmp_word)->heredoc)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	if ((*tmp_token)->type == 7)
		(*tmp_word)->type_heredoc = 1;
	else
		(*tmp_word)->type_heredoc = -1;
}

int	heredoc_init(t_command **tmp_word, t_token **tmp_token, t_shell *shell)
{
	char	*str;

	str = "minishell: syntax error near unexpected token `newline'\n";
	if ((*tmp_token)->next)
	{
		(*tmp_token) = (*tmp_token)->next;
		if ((*tmp_token)->next && ((*tmp_token)->type == 8
				|| ft_strcmp((*tmp_token)->value, "") == 0))
			if_token_next(tmp_token);
		if (is_redir((*tmp_token)->value, shell))
			return (-1);
		if ((*tmp_word)->heredoc == NULL && (*tmp_token)->type != 8)
		{
			if_heredoc(tmp_word, tmp_token, shell);
			if (execute_heredoc((*tmp_word), shell) == -1)
				return (-1);
		}
	}
	if ((!(*tmp_word)->heredoc))
	{
		set_unsigned_status(SYNTAX_ERROR);
		return (error_message(str, NULL, NULL), -1);
	}
	return (0);
}
