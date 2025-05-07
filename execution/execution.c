/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:06:02 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 21:06:05 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	create_process(t_shell *shell, char *full_path,
	t_command *cmd, bool exec_flag)
{
	pid_t	pid;
	int		temp_status;

	temp_status = 0;
	pid = fork();
	if (pid == 0)
		if_pid_is_zero(shell, full_path, cmd, exec_flag);
	else if (pid < 0)
		perror("fork");
	else
		waitpid(pid, &temp_status, 0);
	if (WIFSIGNALED(temp_status))
	{
		if (temp_status == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (temp_status == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		temp_status += 128;
		set_unsigned_status(temp_status);
	}
	else
		set_unsigned_status(proccess_exit_code(temp_status));
}

void	execute_without_pipe(t_shell *shell, t_command *cmd, char *full_path)
{
	int		status;
	bool	exec_flag;

	status = 1;
	exec_flag = true;
	if (is_builtin(cmd) == 1 && shell->pipe_count == 0)
		status = builtin(shell, cmd);
	if ((status == 0 || status == -1))
		return ;
	if (path_case(shell, cmd, &full_path) == -1)
		return ;
	minishell_signals(NON_INTERACTIVE_SIGN, cmd);
	create_process(shell, full_path, cmd, exec_flag);
	free(full_path);
	full_path = NULL;
}

void	allocate_pipe_fds(t_shell *shell)
{
	int	i;

	i = 0;
	shell->pipe_fds = (int *) malloc(sizeof(int) * shell->pipe_count);
	while (i < shell->pipe_count)
	{
		shell->pipe_fds[i] = -1;
		i++;
	}
}

void	wait_all_forks(t_shell *shell)
{
	int	i;
	int	temp_status;

	i = 0;
	temp_status = 0;
	while (i < shell->pipe_index)
	{
		waitpid(shell->pipe_fds[i], &temp_status, 0);
		i++;
	}
	set_unsigned_status(proccess_exit_code(temp_status));
}

void	execute_command(t_shell *shell)
{
	t_command	*cmd;
	char		*full_path;
	int			status;
	bool		exec_flag;

	status = 1;
	exec_flag = true;
	full_path = NULL;
	cmd = shell->word;
	if (shell->pipe_count == 0)
		execute_without_pipe(shell, cmd, full_path);
	else
	{
		allocate_pipe_fds(shell);
		while (cmd)
		{
			minishell_signals(NON_INTERACTIVE_SIGN, cmd);
			if (cmd->command)
				create_process_pipes(shell, full_path, cmd, exec_flag);
			shell->pipe_count--;
			full_path = free_chr_ptr(full_path);
			cmd = cmd->next;
		}
		wait_all_forks(shell);
	}
}
