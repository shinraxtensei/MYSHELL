/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:33:54 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:37:03 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *to, const void *from, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;

	i = 0;
	if (!to && !from)
		return (NULL);
	dest = (unsigned char *)to;
	src = (unsigned char *)from;
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
		{
			dest[i] = src[i];
			i++;
			return (to + i);
		}
		if (src[i] != (unsigned char)c)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (NULL);
}
