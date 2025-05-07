/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:48:22 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 22:12:33 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment_variables.h>

void	if_input_is_not_backslash_zero(t_shell *shell)
{
	char	*str;

	str = "minishell: syntax error near unexpected token ";
	input_tokenization(shell);
	checking_all_tokens(shell);
	shell->pipe_count_temp = pipe_count(shell);
	if (shell->pipe_count_temp == 0 && shell->pipe_count > 0)
	{
		error_message(str, "|", NULL);
		shell->pipe_count_temp = -1;
		set_unsigned_status(SYNTAX_ERROR);
	}
	if (shell->token && shell->pipe_count_temp > 0 && shell->error_flag != -1)
		if_pipe_count(shell);
	add_history(shell->input);
}

void	if_input_is_backslash_zero(t_shell *shell)
{
	if (shell->handler->lst_cmd != NULL)
		free(shell->handler->lst_cmd);
	shell->handler->lst_cmd = ft_strdup_env("");
	if (!shell->handler->lst_cmd)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
}

void	if_executable_name_is_null(t_shell *shell)
{
	if (!shell->executable_name)
	{
		set_unsigned_status(MALLOC_ERROR);
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
	}
}

void	if_input(t_shell *shell)
{
	if (shell->input[0] != '\0')
		if_input_is_not_backslash_zero(shell);
}

int	if_input_is_null(t_shell *shell)
{
	if (!shell->input)
	{
		write(STDOUT_FILENO, "exit\n", ft_strlen_env("exit\n"));
		free_shell(shell, NO_EXIT, DELETE_ENV, 0);
		return (1);
	}
	return (0);
}
