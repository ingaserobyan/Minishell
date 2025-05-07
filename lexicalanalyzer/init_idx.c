/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_idx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:14:00 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 20:28:40 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_env_init	env_init_idx(void)
{
	t_env_init	idx;

	idx.join = NULL;
	idx.tmp_str = NULL;
	idx.temp = NULL;
	idx.len = 0;
	idx.i = 0;
	idx.j = 0;
	return (idx);
}

t_quates	quates_idx(void)
{
	t_quates	idx;

	idx.i = 0;
	idx.j = 0;
	idx.tmp = 0;
	idx.len = 0;
	idx.count = 0;
	idx.count_quate = 0;
	idx.count_double_quate = 0;
	idx.flag_open = 0;
	idx.flag_close = 0;
	idx.flag = 0;
	idx.error_flag = 0;
	return (idx);
}

t_command_args	command_args_idx(t_shell *shell)
{
	t_command_args	idx;

	idx.i = 0;
	idx.count = 0;
	idx.tmp_word = shell->word;
	idx.tmp_token = shell->token;
	idx.start_token = NULL;
	idx.new_node = NULL;
	return (idx);
}

t_find_executable	find_executable_idx(void)
{
	t_find_executable	idx;

	idx.i = 0;
	idx.len = 0;
	idx.token = NULL;
	idx.full_path = NULL;
	idx.tmp_full_path = NULL;
	idx.path_env = NULL;
	idx.path_copy = NULL;
	return (idx);
}

void	init_all_structs(t_shell *shell, char *argv)
{
	(void) argv;
	shell->token = NULL;
	shell->handler = NULL;
	shell->word = NULL;
	shell->pwd = NULL;
	shell->oldpwd = NULL;
	shell->heredoc_count = 0;
	shell->pipe_count = 0;
	shell->pipe_count_temp = 0;
	shell->executable_name = NULL;
	shell->error_flag = 1;
	shell->cmd_counter = 0;
	shell->pipe_index = 0;
	shell->seperator_error = 0;
	shell->pipe_fds = NULL;
	shell->input = NULL;
}
