/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:33:51 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:36:59 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*index;
	int		nb;

	if (!lst)
		return (0);
	index = lst;
	nb = 1;
	while (index->next != 0)
	{
		index = index->next;
		nb++;
	}
	return (nb);
}
