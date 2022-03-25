/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:37:40 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/25 11:28:09 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clear(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static int	count_words(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;  
			continue;
		}
		count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

static char	**fill_array_with_words(char **arr, char const *str, char c)
{
	int	index;
	int	i;
	int	tmp_i;

	index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		tmp_i = i;
		while (str[i] != c && str[i])
			i++;
		arr[index] = malloc(i - tmp_i + 1);
		if (!arr[index])
			return (NULL);
		ft_strlcpy(arr[index++], str + tmp_i, i - tmp_i + 1);
	}
	arr[index] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words_count;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	array = malloc((words_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (!fill_array_with_words(array, s, c))
	{
		clear(array);
		return (NULL);
	}
	return (array);
}
