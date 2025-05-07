/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:34:11 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:34:16 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	if_type_five(t_shell *shell, t_command **tmp_word)
{
	shell->heredoc_count--;
	if (!(shell->heredoc_count <= 0))
	{
		free((*tmp_word)->heredoc);
		(*tmp_word)->heredoc = NULL;
	}
}

int	is_heredoc(t_command **tmp_word,
t_token **tmp_token, t_shell *shell)
{
	if ((*tmp_token)->type == 5 && (*tmp_word)->heredoc == NULL)
	{
		if (heredoc_init(tmp_word, tmp_token, shell) == -1)
			return (-1);
	}
	else if ((*tmp_token)->type == 5 && (*tmp_word)->heredoc != NULL)
	{
		if_type_five(shell, tmp_word);
		if (heredoc_init(tmp_word, tmp_token, shell) == -1)
			return (-1);
	}
	return (0);
}

int	redirection_init(t_command **tmp_word,
t_token **tmp_token, t_shell *shell)
{
	if ((*tmp_token)->type == 3 && (*tmp_word)->error_flag == 0)
	{
		if ((*tmp_word)->red_out != NULL)
			free((*tmp_word)->red_out);
		if (redirection_out(tmp_word, tmp_token, shell) == -1)
			return (-1);
	}
	else if ((*tmp_token)->type == 2 && (*tmp_word)->error_flag == 0)
	{
		if ((*tmp_word)->red_in != NULL)
			free((*tmp_word)->red_in);
		if (redirection_in(tmp_word, tmp_token, shell) == -1)
			return (-1);
	}
	else if ((*tmp_token)->type == 4 && (*tmp_word)->error_flag == 0)
	{
		if (redirection_append(tmp_word, tmp_token, shell) == -1)
			return (-1);
	}
	else
	{
		if (is_heredoc(tmp_word, tmp_token, shell) == -1)
			return (-1);
	}
	return (0);
}
