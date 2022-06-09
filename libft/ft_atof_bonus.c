/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:35:36 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float	get_nbr_after_dot(const char *str, int i, float nbr, int np)
{
	int	count;

	count = 1;
	if (str[i] == '.')
		i++;
	else
		return (nbr * np);
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		count = count * 10;
	}
	return ((nbr / count) * np);
}

float	ft_atof(const char *str)
{
	int		i;
	int		np;
	float	nbr;

	i = 0;
	nbr = 0;
	np = 1;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (str[i] != '\0' && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			np = np * -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (get_nbr_after_dot(str, i, nbr, np));
}
