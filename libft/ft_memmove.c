/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:37:15 by ahouari           #+#    #+#             */
/*   Updated: 2022/02/11 08:37:17 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (dest > src)
		while (n--)
			*(char *)(dest + n) = *(char *)(src + n);
	else if (dest < src)
		while (++i < n)
			*(char *)(dest + i) = *(char *)(src + i);
	return (dest);
}
