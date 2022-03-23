/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:38:33 by ahouari           #+#    #+#             */
/*   Updated: 2022/02/11 08:38:34 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*last_occ;

	last_occ = NULL;
	i = 0;
	while (str[i])
		if (str[i++] == (char) c)
			last_occ = (char *)str + i - 1;
	if (!c)
		return ((char *)str + i);
	return (last_occ);
}
