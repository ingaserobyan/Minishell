/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:55:27 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:29 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

int	nodes_are_same(t_node *node_1, t_node *node_2)
{
	return (node_1 == node_2);
}

void	put_nills(t_node *node, t_tree *tree)
{
	node->right = tree->nill;
	node->left = tree->nill;
}

int	nodes_cmp(t_node *node_1, t_node *node_2)
{
	return (ft_strcmp_env(node_1->key, node_2->key));
}

char	*ft_strnstr_env(char *haystack, char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (ft_strlen_env(needle) == 0)
		return ((char *)haystack);
	if ((len == 0) || (ft_strlen_env(needle) > ft_strlen_env(haystack)))
		return (NULL);
	while ((i + ft_strlen_env(needle)) <= len)
	{
		if (ft_strcmp_env(haystack, needle) == 0)
			return ((char *)(haystack));
		++i;
		++haystack;
	}
	return (NULL);
}
