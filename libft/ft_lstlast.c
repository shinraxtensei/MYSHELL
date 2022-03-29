/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:36:46 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/29 11:20:32 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *tmp;
	if (!lst)
		return (NULL);
	tmp  =lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
