/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:48:46 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:48:46 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <environment_variables.h>

void	update_lst_cmd(t_shell *shell)
{
	t_command	*lst_cmd;

	lst_cmd = shell->word;
	while (lst_cmd->next)
	{
		lst_cmd = lst_cmd->next;
	}
	if (shell->handler->lst_cmd != NULL)
		free(shell->handler->lst_cmd);
	shell->handler->lst_cmd = ft_strdup(lst_cmd->command);
	if (!shell->handler->lst_cmd)
	{
		set_unsigned_status(MALLOC_ERROR);
		free_shell(shell, LAST_EXIT, DELETE_ENV, get_status());
	}
}

int	execute_buitin(t_shell *shell, t_command *tmp_word)
{
	int	status;

	status = 1;
	if (ft_strcmp_ultra(tmp_word->command, "pwd") == 0)
		status = ft_pwd(tmp_word->args, shell);
	else if (ft_strcmp(tmp_word->command, "cd") == 0)
		status = ft_cd(tmp_word->args, shell->handler,
				shell->executable_name, shell);
	else if (ft_strcmp_ultra(tmp_word->command, "echo") == 0)
		status = ft_echo(tmp_word->args);
	else if (ft_strcmp(tmp_word->command, "export") == 0)
		status = ft_export(tmp_word->args, shell->handler,
				shell->executable_name, shell);
	else if (ft_strcmp_ultra(tmp_word->command, "env") == 0)
		status = ft_env(tmp_word->args, shell->handler, shell);
	else if (ft_strcmp(tmp_word->command, "unset") == 0)
		status = ft_unset(tmp_word->args, shell->handler,
				shell->executable_name, 1);
	else if (ft_strcmp(tmp_word->command, "exit") == 0)
		status = ft_exit(shell);
	return (status);
}

int	builtin(t_shell *shell, t_command *tmp_word)
{
	int	status;
	int	red_or_in;
	int	red_or_out;

	status = 1;
	red_or_in = dup(0);
	red_or_out = dup(1);
	feragamo(tmp_word);
	status = execute_buitin(shell, tmp_word);
	if (status == -1)
		status = 0;
	dup2(red_or_in, 0);
	dup2(red_or_out, 1);
	return (status);
}

int	is_builtin(t_command *tmp_word)
{
	int	status;

	status = 0;
	if (ft_strcmp_ultra(tmp_word->command, "pwd") == 0)
		status = 1;
	if (ft_strcmp(tmp_word->command, "cd") == 0)
		status = 1;
	else if (ft_strcmp_ultra(tmp_word->command, "echo") == 0)
		status = 1;
	else if (ft_strcmp(tmp_word->command, "export") == 0)
		status = 1;
	else if (ft_strcmp_ultra(tmp_word->command, "env") == 0)
		status = 1;
	else if (ft_strcmp(tmp_word->command, "unset") == 0)
		status = 1;
	else if (ft_strcmp(tmp_word->command, "exit") == 0)
		status = 1;
	return (status);
}
