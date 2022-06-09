/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:34:04 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:37:18 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*backward(char *dest, char *src, size_t n)
{
	while (n > 0)
	{
		dest[n - 1] = src[n - 1];
		n--;
	}
	return (dest);
}

static char	*forward(char *dest, char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *to, const void *from, size_t n)
{
	char	*dest;
	char	*src;

	if (!to && !from)
		return (0);
	dest = (char *)to;
	src = (char *)from;
	if (src < dest)
		backward(dest, src, n);
	else
		forward(dest, src, n);
	return (to);
}
