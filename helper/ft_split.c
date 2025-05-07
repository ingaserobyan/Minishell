/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmelikya <gmelikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:25:47 by gmelikya          #+#    #+#             */
/*   Updated: 2025/01/19 17:25:49 by gmelikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment_variables.h"

static size_t	ft_words(char const *str, char c)
{
	size_t	i;
	size_t	count;

	i = 1;
	count = 0;
	if (!str)
		return (0);
	if (str[0] != c)
		count++;
	while (str[i] != '\0')
	{
		if ((str[i - 1] == c) && (str[i] != c))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static size_t	free_split(char **str, size_t word_count)
{
	size_t	i;

	i = 0;
	while (i < word_count)
	{
		free(str[i]);
		str[i] = 0;
		++i;
	}
	free(str);
	return (0);
}

size_t	gwl(const char *s, char c, size_t start)
{
	size_t	len;

	len = 0;
	while (s[start + len] != c && s[start + len] != '\0')
		len++;
	return (len);
}

static size_t	extract_word(char **str, const char *s, char c, size_t j)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (i < ft_words(s, c))
	{
		len = j;
		if (s[j] != c)
		{
			str[i] = (char *)malloc(sizeof(char) * (gwl(s, c, len) + 1));
			if (!str)
				return (free_split(str, ft_words(s, c) + 1));
			len = 0;
			while (s[j] != c && s[j] != '\0')
				str[i][len++] = s[j++];
			str[i++][len] = '\0';
		}
		else
			j++;
	}
	str[i] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	if (*s == '\0')
	{
		str = malloc(sizeof(char *));
		if (!str)
			return (NULL);
		str[0] = NULL;
		return (str);
	}
	str = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!str)
		return (NULL);
	extract_word(str, s, c, 0);
	return (str);
}
