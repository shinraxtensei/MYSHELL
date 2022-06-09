/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:34:48 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:38:18 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkl(const char *big, const char *little, size_t len, size_t i)
{
	int	a;

	a = 0;
	while (i < len && little[a] != '\0' && big[i] != '\0')
	{
		if (big[i] != little[a])
			return (0);
		a++;
		i++;
	}
	if (little[a] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!(*little))
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (little[0] == big[i] && checkl(big, little, len, i) == 1)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
