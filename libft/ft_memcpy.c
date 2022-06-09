/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:34:02 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:37:14 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			i;

	if (!(to) && !(from))
		return (0);
	dest = (unsigned char *)to;
	src = (unsigned char *)from;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (to);
}
