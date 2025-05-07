/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:37 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:54:38 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

void	error_msg_env(char *s1, char *s2, char *s3, char *s4)
{
	if (s1)
		write(2, s1, ft_strlen_env(s1));
	if (s2)
	{
		write(2, ": ", 2);
		write(2, s2, ft_strlen_env(s2));
	}
	if (s3)
	{
		write(2, ": ", 2);
		write(2, s3, ft_strlen_env(s3));
	}
	if (s4)
	{
		write(2, ": ", 2);
		write(2, s4, ft_strlen_env(s4));
	}
	write(2, "\n", 1);
}

char	*cut_until(char *line, char c)
{
	int		len;
	char	*new_str;

	len = 0;
	new_str = NULL;
	if (!line)
		return (NULL);
	while (line[len] && line[len] != c)
		len++;
	new_str = ft_strlcat_env(line, len);
	return (new_str);
}

char	*cut_after(char *line, char c)
{
	int		len;
	char	*new_str;

	len = 0;
	new_str = NULL;
	if (!line)
		return (NULL);
	while (line[len] != c && line[len] != '\0')
		len++;
	if (line[len] == c && line[len + 1] == '\0')
	{
		new_str = ft_strdup_env("");
		if (!new_str)
			set_unsigned_status(MALLOC_ERROR);
		return (new_str);
	}
	if (line[len] == '\0')
		return (NULL);
	len++;
	new_str = ft_strlcat_env((line + len), ft_strlen_env(line + len));
	return (new_str);
}

char	*cut_replace(char *stack, char *needle, char *replace)
{
	t_cut_helper	ch;

	if (!stack || !needle)
		return (NULL);
	if (init_cut_helper(&ch, stack, needle, replace) == 1)
		return (NULL);
	while (stack[ch.i] != '\0')
	{
		if (ft_strncmp_env((stack + ch.i), needle, ft_strlen_env(needle)) == 0)
		{
			ch.j = 0;
			ch.k = 0;
			while (ch.j < ch.i)
				ch.new_str[ch.j] = stack[(ch.j)++];
			while (ch.k < ft_strlen_env(replace))
				ch.new_str[ch.j++] = replace[ch.k++];
			ch.i = ch.i + ft_strlen_env(needle);
			while (ch.i < ft_strlen_env(stack))
				ch.new_str[ch.j++] = stack[ch.i++];
			ch.new_str[ch.j] = '\0';
			return (ch.new_str);
		}
		ch.i++;
	}
	return (NULL);
}
