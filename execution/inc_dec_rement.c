/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inc_dec_rement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:13:37 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 21:49:31 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

extern void	rl_replace_line(char *c, int d);

void	increment_shlvl(t_shell *shell)
{
	t_node	*node;

	node = NULL;
	node = search_node(shell->handler->tree, "SHLVL");
	shell->shlvl = ft_atoi(node->value);
	free(node->value);
	if (shell->shlvl < 0)
		node->value = ft_itoa(0);
	else if (shell->shlvl > 9999)
		node->value = ft_itoa(1);
	else
		node->value = ft_itoa(shell->shlvl + 1);
	if (!(node->value))
	{
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	}
}

int	proccess_exit_code(int temp_status)
{
	int	exit_code;

	exit_code = 0;
	exit_code = (temp_status >> 8) & 0xFF;
	return (exit_code);
}

void	error_message(char *str, char *str2, char *str3)
{
	char	*tmp_join;
	char	*join;

	if (str3 != NULL)
	{
		write(2, str, ft_strlen(str));
		write(2, str2, ft_strlen(str2));
		write(2, ": ", 2);
		write(2, str3, ft_strlen(str3));
		write(2, "\n", 1);
	}
	else if (str2 != NULL)
	{
		tmp_join = ft_strjoin(str, str2);
		join = ft_strjoin(tmp_join, "\n");
		write(2, join, ft_strlen(join));
		free(tmp_join);
		free(join);
		return ;
	}
	else
		write(2, str, ft_strlen(str));
}

void	sig_heredoc(int signal)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	set_unsigned_status(SIGNAL_STATUS);
	(void)signal;
}
