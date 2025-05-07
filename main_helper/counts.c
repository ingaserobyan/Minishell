/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:47:14 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 19:19:59 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment_variables.h>

void	count_heredoc(t_shell *shell)
{
	t_token	*tmp_token;

	tmp_token = shell->token;
	while (tmp_token)
	{
		if (tmp_token->type == 5)
			shell->heredoc_count++;
		tmp_token = tmp_token->next;
	}
}

void	word_count(t_shell *shell)
{
	t_command	*tmp;

	tmp = shell->word;
	while (tmp)
	{
		shell->word_count++;
		tmp = tmp->next;
	}
}

int	pipe_count(t_shell *shell)
{
	t_token	*tmp;
	int		flag_pipe;

	flag_pipe = 0;
	tmp = shell->token;
	while (tmp)
	{
		if (tmp->type == 1)
		{
			shell->pipe_count++;
			flag_pipe = 0;
		}
		if (tmp->type != 1 && tmp->type != 8)
			flag_pipe++;
		tmp = tmp->next;
	}
	return (flag_pipe);
}

void	if_pipe_count(t_shell *shell)
{
	t_command	*lst_cmd;
	char		*str;
	int			error_commands_and_args;

	str = "minishell: Resource temporarily unavailable\n";
	error_commands_and_args = commands_and_args(shell);
	word_count(shell);
	lst_cmd = shell->word;
	while (lst_cmd->next != NULL)
		lst_cmd = lst_cmd->next;
	if (shell->word->error_flag > -1
		&& error_commands_and_args == 0
		&& shell->pipe_count == 0 && shell->word->exist_cmd > -1)
		execute_command(shell);
	else if (shell->seperator_error > -1 && shell->pipe_count > 0
		&& shell->pipe_count <= 331 && shell->pipe_count_temp > 0)
		execute_command(shell);
	else if (shell->pipe_count > 331)
	{
		error_message(str, NULL, NULL);
		set_unsigned_status(1);
	}
}
