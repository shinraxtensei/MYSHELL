/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:30:08 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_content(char *var)
{
	int		i;
	t_env	*env_var;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	env_var = (t_env *)calloc_or_exit(sizeof(t_env), 1);
	env_var->name = ft_substr(var, 0, i);
	if (ft_strncmp("SHLVL", env_var->name, 5) == 0)
		env_var->value = ft_itoa(ft_atoi(var + i + 1) + 1);
	else if (var[i])
		env_var->value = ft_strdup(var + i + 1);
	else
		env_var->value = NULL;
	return (env_var);
}

t_list	*init_env_lst(char **envp)
{
	int		i;
	t_env	*env_var;
	t_list	*env_lst;

	i = 0;
	env_lst = NULL;
	while (envp[i])
	{
		env_var = new_env_content(envp[i]);
		ft_lstadd_back(&env_lst, ft_lstnew((void *)env_var));
		i++;
	}
	if (!get_env_lst("OLDPWD", env_lst))
	{
		env_var = new_env_content("OLDPWD");
		ft_lstadd_back(&env_lst, ft_lstnew((void *)env_var));
	}
	return (env_lst);
}

t_list	*copy_env_lst(t_list *original)
{
	t_env	*env_var;
	t_list	*copy;

	copy = NULL;
	while (original)
	{
		env_var = (t_env *)malloc(sizeof(t_env));
		env_var->name = ft_strdup(get_env_lst_name(original));
		if (get_env_lst_value(original))
			env_var->value = ft_strdup(get_env_lst_value(original));
		else
			env_var->value = NULL;
		ft_lstadd_back(&copy, ft_lstnew((void *)env_var));
		original = original->next;
	}
	return (copy);
}

void	del_env_content(void *env_var)
{
	free(((t_env *)env_var)->name);
	if (((t_env *)env_var)->value)
		free(((t_env *)env_var)->value);
	free(env_var);
}

void	delone_env_lst(t_list *to_del, t_list **env)
{
	t_list	*curr;

	if (!to_del || !env)
		return ;
	if (*env == to_del)
	{
		*env = (*env)->next;
		ft_lstdelone(to_del, &del_env_content);
		return ;
	}
	curr = *env;
	while (curr->next)
	{
		if (curr->next == to_del)
		{
			curr->next = to_del->next;
			ft_lstdelone(to_del, &del_env_content);
			return ;
		}
		curr = curr->next;
	}
}
