/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:53:07 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:53:11 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	set_color_black(t_node *node)
{
	if (node)
		node->color = BLACK;
}

void	set_color_red(t_node *node)
{
	if (node)
		node->color = RED;
}
