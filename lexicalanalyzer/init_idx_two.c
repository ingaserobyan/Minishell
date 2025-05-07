/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_idx_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:37:33 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:37:35 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_count	init_count(void)
{
	t_count	val_count;

	val_count.count_env = 0;
	val_count.count_pipe = 0;
	val_count.count_r_in = 0;
	val_count.count_r_out = 0;
	val_count.i = 0;
	return (val_count);
}

t_init	init_idx(void)
{
	t_init	idx;

	idx.len_redir = 0;
	idx.len_pipe = 0;
	idx.j = 0;
	idx.tmp = 0;
	idx.str = NULL;
	return (idx);
}

t_env_heredoc	init_env_heredoc(void)
{
	t_env_heredoc	idx;

	idx.i = 0;
	idx.flag = 0;
	idx.j = idx.i;
	idx.len = 0;
	idx.join = NULL;
	idx.temp = NULL;
	idx.tmp_str = NULL;
	idx.var_value = NULL;
	return (idx);
}

void	clear_idx(t_command_args *idx)
{
	idx->i = 0;
	idx->count = 0;
	idx->new_node = NULL;
}
