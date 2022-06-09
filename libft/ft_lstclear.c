/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:33:37 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:36:39 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*index;
	t_list	*temp;

	index = *lst;
	while (index->next != 0)
	{
		temp = index->next;
		ft_lstdelone(index, del);
		index = temp;
	}
	ft_lstdelone(index, del);
	*lst = NULL;
}
