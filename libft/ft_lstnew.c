/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:36:56 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/29 13:06:40 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int arr_couter(char **strs)
// {
//     int len = 0;
//     while (strs[len])
//         len++;
//     return len;
// }



// t_list    *ft_lstnew(void *command)
// {

//     t_list *new;
//     new  = malloc(sizeof(t_list));
//     if(!(new->whole_command = split_things((char *)command, ' ')))
//     {   
//         exit(1);
//     }

//     new->cmd = ft_strdup(new->whole_command[0]);
//     if (arr_couter(new->whole_command) > 1)
//         new->args = &new->whole_command[1];
//     new->next = NULL;
//     return (new);
// }
t_list	*ft_lstnew(void *command)
{
	t_list	*new;
	
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->command = command;
	new->next = NULL;
	return (new);
}