/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:39:07 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:39:09 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	put_type_to_token(int *i, t_shell *shell, t_token *node)
{
	if (shell->input[*i] == '|')
		node->type = TOKEN_PIPE;
	else if (shell->input[*i] == '>' && shell->input[(*i) + 1] == '>')
		node->type = TOKEN_REDIR_APPEND;
	else if (shell->input[*i] == '<' && shell->input[(*i) + 1] == '<')
		node->type = TOKEN_REDIR_HEREDOC;
	else if (shell->input[*i] == '>')
		node->type = TOKEN_REDIR_OUT;
	else if (shell->input[*i] == '<')
		node->type = TOKEN_REDIR_IN;
	else if (shell->input[*i] == '$')
		node->type = TOKEN_ENV_VAR;
	else if (shell->input[*i] == '"' || shell->input[*i] == '\'')
		node->type = TOKEN_QUOTES;
	else if (is_white_space(shell->input[*i]))
		node->type = TOKEN_SPACE;
	else
		node->type = TOKEN_WORD;
}

t_token	*new_node(int *i, t_shell *shell, int *error_flag)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
	node->var_value = NULL;
	node->next = NULL;
	node->key = NULL;
	put_type_to_token(i, shell, node);
	token_value(i, shell, &node, error_flag);
	if ((*error_flag) == -1)
	{
		free(node);
		node = NULL;
	}
	return (node);
}

int	create_list(t_shell *shell, int i, t_token **prev_prev, t_token **tmp)
{
	int	error_flag;

	error_flag = 0;
	if (!shell->token)
	{
		shell->token = new_node(&i, shell, &error_flag);
		if (!shell->token)
			return (i);
		if (shell->token)
			(*tmp) = shell->token;
	}
	else
	{
		(*prev_prev) = *tmp;
		(*tmp)->next = new_node(&i, shell, &error_flag);
		if (!(*tmp)->next && error_flag == 0)
			free_shell(shell, LAST_EXIT, DELETE_ENV, MALLOC_ERROR);
		if ((*tmp)->next)
			(*tmp) = (*tmp)->next;
	}
	if (error_flag == -1)
		return (-1);
	return (i);
}

int	while_input(t_shell *shell, int *i, t_token **tmp, t_token **prev_prev)
{
	if ((*tmp) && ((*tmp)->value == NULL))
	{
		del_node(&shell->token, (*tmp));
		tmp = prev_prev;
	}
	if (is_white_space(shell->input[*i]))
		*i = create_list(shell, *i, prev_prev, tmp);
	while ((*tmp) && is_white_space(shell->input[*i]))
		(*i)++;
	return (*i);
}

void	input_tokenization(t_shell *shell)
{
	int		i;
	t_token	*prev_prev;
	t_token	*tmp;

	i = 0;
	prev_prev = NULL;
	while (shell->input[i] && is_white_space(shell->input[i]))
		i++;
	while (shell->input[i])
	{
		i = create_list(shell, i, &prev_prev, &tmp);
		if (shell == NULL || shell->token == NULL || i == -1)
		{
			shell->error_flag = i;
			return ;
		}
		i = while_input(shell, &i, &tmp, &prev_prev);
	}
	if (if_its_control_operator(shell) == -1)
	{
		shell->error_flag = -1;
		return ;
	}
}
