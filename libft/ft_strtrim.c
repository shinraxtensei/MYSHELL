/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:34:53 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:38:35 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*trim_more(char *trim, char const *s1, int start, int end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*trim;
	size_t		start;
	size_t		end;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (check_set(s1[start], set) == 1)
		start++;
	if (start == end)
	{
		trim = (char *)malloc(sizeof(char) * 1);
		trim[0] = 0;
		return (trim);
	}
	while (check_set(s1[end - 1], set) == 1)
		end--;
	trim = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!(trim))
		return (NULL);
	trim_more(trim, s1, start, end);
	return (trim);
}
