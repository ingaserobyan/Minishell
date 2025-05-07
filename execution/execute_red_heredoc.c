/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_red_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:04:59 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:24:04 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	execute_in(t_command *cmd)
{
	if (cmd->fd_in > -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(cmd->fd_in);
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
}

void	execute_out(t_command *cmd)
{
	if (cmd->fd_out > -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			close(cmd->fd_out);
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_out);
	}
}

int	if_heredoc_cnt(t_shell *shell)
{
	if (shell->heredoc_count >= 16)
	{
		error_message("minishell: maximum here-document count exceeded\n",
			NULL, NULL);
		set_unsigned_status(2);
		free_shell(shell, LAST_EXIT, DELETE_ENV, 2);
		return (-1);
	}
	return (0);
}

void	while_no_break(t_command **cmd, t_shell *shell, char *input)
{
	minishell_signals(HEREDOC_SIGN, NULL);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, (*cmd)->heredoc) == 0)
			break ;
		if (get_status() == SIGNAL_STATUS)
		{
			write(1, "> \n", ft_strlen("> \n"));
			(*cmd)->command = free_chr_ptr((*cmd)->command);
			break ;
		}
		if ((*cmd)->type_heredoc == -1)
			hdoc_dollar_cvrtr(&input, shell);
		write((*cmd)->fd_in, input, ft_strlen(input));
		write((*cmd)->fd_in, "\n", 1);
		free(input);
		set_unsigned_status(0);
	}
	set_unsigned_status(get_status());
	close((*cmd)->fd_in);
	free(input);
}

int	execute_heredoc(t_command *cmd, t_shell *shell)
{
	char	*input;

	input = NULL;
	if (if_heredoc_cnt(shell) == -1)
		return (-1);
	cmd -> fd_in = open("heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (cmd -> fd_in < 0)
	{
		cmd->error_flag = -1;
		perror("minishell: ");
		exit(EXIT_FAILURE);
	}
	while_no_break(&cmd, shell, input);
	cmd -> fd_in = open("heredoc.txt", O_RDONLY);
	if (cmd -> fd_in == -1)
	{
		perror("Error opening temp file for heredoc");
		exit(EXIT_FAILURE);
	}
	unlink("heredoc.txt");
	return (0);
}
