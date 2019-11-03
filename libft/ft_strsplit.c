/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yenhang1@gmail.co>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:17:24 by yehuang           #+#    #+#             */
/*   Updated: 2019/07/26 23:27:13 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static size_t	word_len(char const *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		*next_word(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return ((char *)s);
}

static	int		countwords(char *str, char c)
{
	int result;
	int i;

	i = 0;
	result = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			i++;
		result++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (result);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	cur;
	size_t	wordcount;

	if (s)
	{
		wordcount = countwords((char *)s, c);
		split = (char **)ft_memalloc((wordcount + 1) * sizeof(char *));
		if (split == NULL)
			return (NULL);
		cur = 0;
		while (cur < wordcount)
		{
			s = next_word(s, c);
			split[cur] = ft_strsub(s, 0, word_len(s, c));
			if (split[cur] == NULL)
				return (NULL);
			cur++;
			s += word_len(s, c);
		}
		split[wordcount] = NULL;
		return (split);
	}
	return (NULL);
}
