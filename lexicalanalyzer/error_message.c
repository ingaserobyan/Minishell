/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:35:53 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 20:33:59 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	free_command_args(t_shell *shell)
{
	t_command	*current;
	t_command	*next;

	current = (shell->word);
	next = shell->word->next;
	if (!shell)
		return ;
	if (!(shell)->word)
		return ;
	while (current)
	{
		next = current->next;
		del_command_args(current);
		free(current);
		current = next;
	}
	shell->word = NULL;
}

void	free_t_token(t_shell *shell)
{
	t_token	*next;
	t_token	*current;

	if (!shell)
		return ;
	if (!(shell)->token)
		return ;
	current = shell -> token;
	while (current)
	{
		next = current ->next;
		if (current->value)
			free(current->value);
		if (current->var_value)
			free(current->var_value);
		if (current->key)
			free(current->key);
		free(current);
		current = next;
	}
	(shell)->token = NULL;
}

void	equals_zero(t_shell *shell)
{
	shell->heredoc_count = 0;
	shell->seperator_error = 0;
	shell->executable_name = NULL;
	shell->input = NULL;
	shell->oldpwd = NULL;
	shell->pwd = NULL;
	shell->pipe_fds = NULL;
	shell->pipe_index = 0;
}

void	free_shell_details(t_shell *shell)
{
	if (shell->token)
		free_t_token(shell);
	if (shell->word)
		free_command_args(shell);
	if (shell->input)
		free(shell->input);
	if (shell->executable_name)
		free(shell->executable_name);
	if (shell->oldpwd)
		free(shell->oldpwd);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->pipe_fds)
		free(shell->pipe_fds);
}

void	free_shell(t_shell *shell, int exit_flag, int env_flag, int exit_status)
{
	set_unsigned_status(exit_status);
	if (shell)
	{
		if (env_flag == DELETE_ENV)
		{
			if (shell->handler)
				delete_handler(shell);
		}
		free_shell_details(shell);
	}
	if (exit_flag == LAST_EXIT)
		exit(get_status());
	equals_zero(shell);
}
