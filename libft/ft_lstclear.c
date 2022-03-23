/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:36:30 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/23 09:33:03 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{

	if (!lst || !del)
		return ;
	while (*lst)
	{
		del((*lst)->command);
		*lst = (*lst)->next;
	}
	*lst = NULL;
}
