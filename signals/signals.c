/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:54:51 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 22:12:49 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

extern void	rl_replace_line(char *c, int d);

void	cat_signal(int signal)
{
	set_unsigned_status(130);
	(void)signal;
}

void	sigint_interactive(int signal)
{
	set_unsigned_status(1);
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)signal;
}

void	sigint_not_interactive(int signal)
{
	set_unsigned_status(1);
	(void)signal;
}

void	sig_quit(int signal)
{
	(void)signal;
}

void	minishell_signals(int type, t_command *cmd)
{
	if (type == INTERACTIVE_SIGN)
	{
		signal(SIGINT, sigint_interactive);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == NON_INTERACTIVE_SIGN)
	{
		if (cmd && ft_strcmp_env(cmd->command, "cat") == 0)
			signal(SIGINT, cat_signal);
		else
			signal(SIGINT, sigint_not_interactive);
		signal(SIGQUIT, sig_quit);
	}
	else if (type == HEREDOC_SIGN)
	{
		signal(SIGINT, sig_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
