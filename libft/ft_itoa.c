/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:33:30 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:36:30 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_putnbr(long int nb, char *str, int size)
{
	int	check_n;

	check_n = 0;
	if (nb < 0)
	{
		check_n++;
		nb = -nb;
	}
	str[size - 1] = '\0';
	while (--size > 0)
	{
		str[size - 1] = '0' + nb % 10;
		nb = nb / 10;
	}
	if (check_n == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int			size;
	long int	nb;
	char		*str;

	nb = (long int)n;
	size = 2;
	if (n < 0)
		size++;
	while ((n / 10) != 0)
	{
		size++;
		n = n / 10;
	}
	str = (char *)ft_calloc(sizeof(char), size);
	if (!(str))
		return (NULL);
	return (ft_putnbr(nb, str, size));
}
