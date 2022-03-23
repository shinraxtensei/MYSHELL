/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:38:28 by ahouari           #+#    #+#             */
/*   Updated: 2022/02/11 08:38:30 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	j;

	if (len == 0 && n[0])
		return (NULL);
	if (!n[0])
		return ((char *)h);
	i = -1;
	while (++i < len && h[i])
	{
		j = -1;
		while (n[++j] && i + j < len)
		{
			if (n[j] != h[i + j])
				break ;
		}
		if (!n[j])
			return ((char *)(h + i));
	}
	return (NULL);
}
