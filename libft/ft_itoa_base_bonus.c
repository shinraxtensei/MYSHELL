/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:33:28 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:36:24 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putnbr_base(unsigned long n, char *base, int size, char *s)
{
	int	l;

	l = ft_strlen(base);
	s[size] = '\0';
	while (size > 0)
	{
		s[size - 1] = base[n % l];
		n = n / l;
		size--;
	}
	return (s);
}

char	*ft_itoa_base(unsigned long int nb, char *base)
{
	unsigned long	l_nb;
	int				l;
	char			*conv;
	int				size;

	l = ft_strlen(base);
	l_nb = nb;
	size = 1;
	while ((nb / l) != 0)
	{
		size++;
		nb = nb / l;
	}
	conv = (char *)ft_calloc(sizeof(char), size + 1);
	if (!(conv))
		return (NULL);
	conv = ft_putnbr_base(l_nb, base, size, conv);
	return (conv);
}
