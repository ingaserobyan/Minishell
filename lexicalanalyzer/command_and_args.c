/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_and_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:34:36 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:34:39 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

t_command	*add_new_node(void)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->command = NULL;
	new_node->args = NULL;
	new_node->red_in = NULL;
	new_node->red_out = NULL;
	new_node->red_append = NULL;
	new_node->heredoc = NULL;
	new_node->type_heredoc = 0;
	new_node->type_command = 0;
	new_node->error_flag = 0;
	new_node->exist_cmd = 0;
	new_node->fd_out = -1;
	new_node->fd_in = -1;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	commands_and_args_helper(t_shell *shell, t_command_args *idx)
{
	while (idx->tmp_token != NULL && ft_strcmp(idx->tmp_token->value, "|") != 0)
	{
		if ((idx->tmp_token->type != 8))
			idx->count++;
		if (idx->tmp_token->next)
			idx->tmp_token = idx->tmp_token->next;
		else
			break ;
	}
	idx->tmp_token = idx->start_token;
	if (shell->word == NULL)
	{
		idx->tmp_word = add_new_node();
		if (!idx->tmp_word)
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		shell->word = idx->tmp_word;
	}
	idx->tmp_word->args = (char **)malloc(sizeof(char *) * (idx->count + 1));
	if (!idx->tmp_word->args)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	idx->tmp_word->args[0] = NULL;
	idx->i = 0;
	idx->count = 0;
}

int	create_cmds_args(t_shell *shell, t_command_args *idx)
{
	while (idx->tmp_token && idx->tmp_token->type != 1)
	{
		if (idx->tmp_token->type == 8)
			idx->tmp_token = idx->tmp_token->next;
		if (idx->tmp_token && idx->tmp_token->type == 1)
			break ;
		idx->start_token = idx->tmp_token;
		commands_and_args_helper(shell, idx);
		if (idx->tmp_token != NULL
			&& ft_strcmp(idx->tmp_token->value, "|") != 0)
		{
			if (struct_init(&(idx->tmp_word),
					&(idx->tmp_token), &(idx->i), shell) == -1)
			{
				idx->tmp_word = idx->tmp_word->next;
				return (-1);
			}
		}
		idx->tmp_word->args[idx->i] = NULL;
		if (idx->tmp_token->next && idx->tmp_token->type != 1)
			idx->tmp_token = idx->tmp_token->next;
		else
			break ;
	}
	return (0);
}

int	commands_and_args(t_shell *shell)
{
	t_command_args	idx;

	count_heredoc(shell);
	idx = command_args_idx(shell);
	while (idx.tmp_token)
	{
		clear_idx(&idx);
		if (create_cmds_args(shell, &idx) == -1)
			return (-1);
		if (idx.tmp_token->type == 1)
		{
			while (idx.tmp_token->next && idx.tmp_token->next->type == 8)
				idx.tmp_token = idx.tmp_token->next;
			if (idx.tmp_token->next == NULL)
			{
				set_unsigned_status(SYNTAX_ERROR);
				return (-1);
			}
			idx.tmp_word->next = add_new_node();
			idx.tmp_word = idx.tmp_word->next;
		}
		idx.tmp_token = idx.tmp_token->next;
	}
	return (0);
}
