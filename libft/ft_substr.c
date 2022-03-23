/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:38:41 by ahouari           #+#    #+#             */
/*   Updated: 2022/02/11 08:38:43 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
	{
		str = malloc(1);
		str[0] = 0;
		return (str);
	}
	str = malloc(len * (len <= slen - start)
			+ (slen - start) * (len > slen - start) + 1);
	if (!str)
		return (NULL);
	i = -1;
	while (++i < slen && i < len)
		str[i] = s[start + i];
	str[i] = 0;
	return (str);
}
