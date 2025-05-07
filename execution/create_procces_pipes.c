/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_procces_pipes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:04:05 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 22:10:02 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	pipe_builtin(t_shell *shell, t_command *cmd)
{
	int	status;

	status = 1;
	if (is_builtin(cmd) == 1)
		status = builtin(shell, cmd);
	if ((status == 0 || status == -1))
		exit(get_status());
	return (status);
}

void	execute_helper(t_shell *shell, t_command *cmd, int *status)
{
	if (cmd->command)
		(*status) = pipe_builtin(shell, cmd);
	feragamo(cmd);
	minishell_signals(NON_INTERACTIVE_SIGN, cmd);
	converter_env_to_ptr(shell->handler, shell);
	if (shell->handler->env == NULL && get_status() == MALLOC_ERROR)
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
}

void	execute_child_proccess(t_shell *shell, char *full_path,
			t_command *cmd, bool exec_flag)
{
	int	status;

	status = 1;
	if (cmd->error_flag == -1)
		exit(1);
	execute_helper(shell, cmd, &status);
	if ((status != 0 || status != -1)
		&& path_case(shell, cmd, &full_path) == -1)
		return ;
	if (cmd->type_command == 6 && ft_strcmp_env(cmd->command, "") == 0)
		exit(0);
	if (cmd->command)
	{
		if (exec_flag && execve(full_path, cmd->args,
				shell->handler->env) == -1)
		{
			error_message("minishell: ", cmd->command, "command not found");
			full_path = free_chr_ptr(full_path);
			exit(127);
		}
	}
	exit(0);
}

void	add_pipe_fd(t_shell *shell, int pid)
{
	shell->pipe_fds[shell->pipe_index] = pid;
	(shell->pipe_index)++;
}

void	create_process_pipes(t_shell *shell, char *full_path,
	t_command *cmd, bool exec_flag)
{
	pid_t		pid;
	int			temp_status;
	int			pipe_fd[2];
	static int	prev_fd_out;

	temp_status = 0;
	if (shell->pipe_count > 0)
		pipe(pipe_fd);
	pid = fork();
	add_pipe_fd(shell, pid);
	if (pid == 0)
	{
		do_child_dups(pipe_fd, prev_fd_out, cmd);
		execute_child_proccess(shell, full_path, cmd, exec_flag);
	}
	else if (pid < 0)
		perror("fork");
	else
		prev_fd_out = do_parent_dups(pipe_fd, prev_fd_out, cmd);
	set_unsigned_status(proccess_exit_code(temp_status));
}
