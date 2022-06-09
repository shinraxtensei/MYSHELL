/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:34:30 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:38:03 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	while (dest[i])
		i++;
	while (src[a] && i + a < size - 1 && size != 0)
	{
		dest[i + a] = src[a];
		a++;
	}
	if (size != 0 || size < i)
		dest[i + a] = 0;
	while (src[a])
		a++;
	if (size < i)
		return (size + a);
	return (i + a);
}
