/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:00:54 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:24:49 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	not_first_cmd(int prev_fd_out)
{
	dup2(prev_fd_out, STDIN_FILENO);
	close(prev_fd_out);
}

void	not_last_cmd(int *pipe_fd)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

void	do_child_dups(int *pipe_fd, int prev_fd_out, t_command *cmd)
{
	if (prev_fd_out > 0)
		not_first_cmd(prev_fd_out);
	if (cmd->next != NULL)
		not_last_cmd(pipe_fd);
	close(pipe_fd[0]);
}

int	do_parent_dups(int *pipe_fd, int prev_fd_out, t_command *cmd)
{
	if (cmd->next != NULL)
		close(pipe_fd[1]);
	if (prev_fd_out != 0)
		close(prev_fd_out);
	prev_fd_out = pipe_fd[0];
	return (prev_fd_out);
}
