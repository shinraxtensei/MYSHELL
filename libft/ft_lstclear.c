/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassamer <eassamer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:36:30 by ahouari           #+#    #+#             */
/*   Updated: 2022/04/23 17:15:23 by eassamer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void del(void *arg)
// {
//     free(arg);
// }

// void	ft_lstclear(t_list **lst, void (*del)(void *))
// {

// 	if (!lst || !del)
// 		return ;
// 	while (*lst)
// 	{
// 		del((*lst)->command->args);
// 		del((*lst)->command->whole_command);
// 		del((*lst)->command->cmd);
//         del((*lst)->command->option);
// 		*lst = (*lst)->next;
// 	}
// 	*lst = NULL;
// }
