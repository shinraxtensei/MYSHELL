/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_linked_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:29:52 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_and_get_middle(t_list *list)
{
	int			i;
	int			half_size;
	t_list		*middle;

	i = 0;
	half_size = ft_lstsize(list) / 2;
	while (i < half_size - 1)
	{
		list = list->next;
		i++;
	}
	middle = list->next;
	list->next = NULL;
	return (middle);
}

t_list	*sort_and_merge(t_list *list1, t_list *list2)
{
	t_list	*to_be_added;
	t_list	*merged_list;

	merged_list = NULL;
	while (list1 || list2)
	{
		if (list1 && (!list2 || ft_strncmp(get_env_lst_name(list1),
					get_env_lst_name(list2), 100) <= 0))
		{
			to_be_added = list1;
			list1 = list1->next;
		}
		else if (list2)
		{
			to_be_added = list2;
			list2 = list2->next;
		}
		to_be_added->next = NULL;
		ft_lstadd_back(&merged_list, to_be_added);
	}
	return (merged_list);
}

void	merge_sort(t_list **list)
{
	t_list	*first;
	t_list	*middle;

	if (!*list || ft_lstsize(*list) <= 1)
		return ;
	first = *list;
	middle = split_and_get_middle(*list);
	merge_sort(&first);
	merge_sort(&middle);
	*list = sort_and_merge(first, middle);
}

void	print_this_message(void)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}
