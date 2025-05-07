/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lib_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:42 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 15:54:44 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

char	*ft_strdup_env(char *s1)
{
	char	*s2;
	size_t	i;

	if (!s1)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * (ft_strlen_env(s1) + 1));
	if (!s2)
	{
		set_unsigned_status(MALLOC_ERROR);
		return (NULL);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int	ft_strcmp_env(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] == s2[i]) && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strlcat_env(char *line, int len)
{
	char	*new_line;
	int		i;

	if (!line || len == 0)
		return (NULL);
	new_line = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_line)
	{
		set_unsigned_status(MALLOC_ERROR);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int	ft_strlen_env(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
		i++;
	return (i);
}

int	ft_strncmp_env(char *s1, char *s2, int len)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (FALSE);
	if (ft_strlen_env(s1) < len)
		return (FALSE);
	if (ft_strlen_env(s2) < len)
		len = ft_strlen_env(s2);
	while (i < len && s1[i])
	{
		if (s1[i] != s2[i])
			return ((s1[i] - s2[i]));
		i++;
	}
	return (0);
}
