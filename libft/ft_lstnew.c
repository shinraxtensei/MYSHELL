/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 08:36:56 by ahouari           #+#    #+#             */
/*   Updated: 2022/03/27 11:16:39 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


int    count_options(char **arr)
{
    int i;
    int len;
    
    i = -1;
    len = 0;
    while(arr[++i])
    {
        if (arr[i][0] == '-')
            len++;
    }
    return (len);
}

t_list    *ft_lstnew(char *arr)
{
    t_list *new;
    int j;
    int i;
    new->command->whole_command = split_things(arr, ' ');
    i = count_options(new->command->whole_command);
    new->command->option = malloc(sizeof(char *) * (i + 1));
    j = -1;
    i = 0;
    new->command->cmd = new->command->whole_command[0];
    while (new->command->whole_command[++i][0] == '-')
        new->command->option[++j] = new->command->whole_command[i];
    new->command->option[j] = 0;
    new->command->args = new->command->whole_command[i];
    return (new);
}