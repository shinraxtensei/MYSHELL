/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:39 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Error handling
 * Export without options 
 * 		- thus it will ignore any flags and not throw out an error
 * Starts with digit or with = : bash: export: `1test': not a valid identifier
 * Has a symbol (/ % * + , - . : ? [] {} ^ ~): 
 * 		bash: export: `/test': not a valid identifier
 * Some symbols are ignored or lead to special behaviour
 * 		 (# & $ ! ; and parsing stuff)
 * Some symbols are accepted (_)
 *
 * Each argument leads to a new variable
 * The variable only has a value if there's an =
 * If one prompts an error, the next one is still added
 */

static void	print_export(t_list *env, int fd_out)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(get_env_lst_name(env), fd_out);
		if (get_env_lst_value(env))
		{
			write(fd_out, "=\"", 2);
			ft_putstr_fd(get_env_lst_value(env), fd_out);
			write(fd_out, "\"", 1);
		}
		write(fd_out, "\n", 1);
		env = env->next;
	}
}

/*
 * - Check if the argument given is correct and while doing so make i point to
 *   the = sign (or the end)
 * - If there's already a variable with that name and a value is given,
 *   update that variable's value
 * - Else, create a new variable
 * I should probably refactor the functions for creating new env content (in
 * utils > env_list) and use it instead of creating this auxiliary function,
 * but I'm lazy.
 */

static void	create_and_add_env_list(char *name, char *value, t_list *env)
{
	t_env	*env_var;

	env_var = (t_env *)calloc_or_exit(sizeof(t_env), 1);
	env_var->name = name;
	env_var->value = value;
	ft_lstadd_back(&env, ft_lstnew((void *)env_var));
}

static int	add_env_list(char *arg, t_list *env)
{
	int		i;
	char	*name;
	char	*value;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	i = 1;
	while (arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] && arg[i] != '=')
		return (1);
	name = ft_substr(arg, 0, i);
	value = NULL;
	if (arg[i])
		value = ft_strdup(arg + i + 1);
	if (get_env_lst(name, env))
	{
		set_env_value(name, value);
		free(name);
		free(value);
	}
	else
		create_and_add_env_list(name, value, env);
	return (0);
}

int	export(t_cmd_table *cmd, t_minishell *minishell)
{
	t_list	*sorted_env;
	int		i;
	int		exit_code;

	if (!cmd->cmd_args[0])
	{
		sorted_env = copy_env_lst(minishell->env);
		merge_sort(&sorted_env);
		print_export(sorted_env, cmd->fd_out);
		ft_lstclear(&sorted_env, &del_env_content);
		return (0);
	}
	i = 0;
	exit_code = 0;
	while (cmd->cmd_args[i])
	{
		if (add_env_list(cmd->cmd_args[i], minishell->env))
		{
			error_message(INVALID_IDENTIFIER);
			exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
