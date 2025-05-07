/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_idx_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:34:57 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 19:40:16 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	del_env_init_idx(t_env_init *idx, int flag)
{
	if (idx->join && flag == -1)
	{
		free(idx->join);
		idx->join = NULL;
	}
	if (idx->tmp_str)
	{
		free(idx->tmp_str);
		idx->tmp_str = NULL;
	}
	idx->len = 0;
}

void	del_command_args(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->command)
		free(cmd->command);
	if (cmd->red_in)
	{
		free(cmd->red_in);
		cmd->red_in = NULL;
	}
	if (cmd->red_out)
		free(cmd->red_out);
	if (cmd->red_append)
		free(cmd->red_append);
	if (cmd->heredoc)
		free(cmd->heredoc);
	while (cmd->args && cmd->args[i])
	{
		free(cmd->args[i]);
		cmd->args[i] = NULL;
		i++;
	}
	free(cmd->args);
}
