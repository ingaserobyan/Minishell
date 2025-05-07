/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:26:39 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:31:21 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	start_checking(int i, t_shell *shell)
{
	if (shell->input[i] == '&' && shell->input[i + 1] == '&')
		error_message("minishell: Error: has_logical_operators\n", NULL, NULL);
}

void	del_node(t_token **head, t_token *tmp)
{
	t_token	*h;

	h = *head;
	if (!head || !*head || !tmp)
		return ;
	if (*head == tmp)
		*head = tmp->next;
	else
	{
		while (h && h->next != tmp)
			h = h->next;
		h->next = tmp->next;
	}
	free(tmp->value);
	free(tmp->var_value);
	free(tmp);
}
