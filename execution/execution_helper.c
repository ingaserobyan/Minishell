/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:06:34 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 22:10:12 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	feragamo(t_command *cmd)
{
	if (cmd->heredoc)
		execute_in(cmd);
	if (cmd->red_in)
		execute_in(cmd);
	if (cmd->red_out)
		execute_out(cmd);
	if (cmd->red_append)
		execute_out(cmd);
}

void	if_pid_is_zero(t_shell *shell, char *full_path,
	t_command *cmd, bool exec_flag)
{
	int	status;

	status = 1;
	if (is_builtin(cmd) == 1)
		status = builtin(shell, cmd);
	if ((status == 0 || status == -1))
		exit(get_status());
	feragamo(cmd);
	if (shell->word->error_flag == -1)
		return ;
	converter_env_to_ptr(shell->handler, shell);
	if (shell->handler->env == NULL && get_status())
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
	minishell_signals(NON_INTERACTIVE_SIGN, cmd);
	if (cmd->type_command == 6 && ft_strcmp_env(cmd->command, "") == 0)
		exit(0);
	if (exec_flag && execve(full_path, cmd->args, shell->handler->env) == -1)
	{
		error_message("minishell: ", cmd->command, "command not found");
		free(full_path);
		exit(127);
	}
	exit(0);
}
