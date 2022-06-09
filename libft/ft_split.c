/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:34:19 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:37:49 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_words(const char *s, char c)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			nb++;
		i++;
	}
	return (nb);
}

static char	**fill_split(const char *s, char c, int words, char **split)
{
	int		i;
	int		word;
	int		letters;

	i = 0;
	word = 0;
	while (word < words)
	{
		while (s[i] && s[i] == c)
			i++;
		letters = 0;
		while (s[i + letters] && s[i + letters] != c)
			letters++;
		split[word] = (char *)malloc(sizeof(char) * (letters + 1));
		if (!split[word])
			return (NULL);
		letters = 0;
		while (s[i] && s[i] != c)
			split[word][letters++] = s[i++];
		split[word++][letters] = 0;
	}
	split[word] = 0;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	words = nb_words(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	fill_split(s, c, words, split);
	return (split);
}
