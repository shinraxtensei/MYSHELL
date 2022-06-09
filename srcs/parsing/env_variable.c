/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:29:06 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 🦕🌴
**
** get_env_var
** 
** Those functions build up a null terminated array**
**	of environement variables.
**	⚠️ If the $ENV_VAR is in between single quotes, it is ignored.
**	1. We get the number of environement variables (while taking the
**		quote rule into account.)
**	2. We get the length of the '$ENV_VAR' written in the instruction
**		line. (Will be used to save that text temporarily when getting
**		the path).
**	3. Then we extract the real path of the env_variable and return the
**		result as an allocated string.
**		If the env_var doesn't exist, we return an empty string.
**
**	Exceptions: 
**	1. 	if we are dealing with $?, we need to expand whatever is
**		behind (for example $?hello might give 100hello). $? calls
**		the last command's exit_code.
**	2.	if there is only '$', we need to return $ unexpanded or modified. 
**
**
** 🌴🥥
*/

int	get_nb_env_var(char	*text)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (text[i])
	{
		quote = check_quote(text[i], quote);
		if (text[i] == '$' && quote != SGL_QUOTE)
			count++;
		i++;
	}
	return (count);
}

/*
** env_var_len = 1 to handle the '$'
*/

int	get_env_var_len(char *text)
{
	int	env_var_len;

	env_var_len = 1;
	while (text[env_var_len] && is_not_exception(text[env_var_len], ENV_VAR))
		env_var_len++;
	return (env_var_len);
}

static char	*get_exit_code(void)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	return (ft_itoa(minishell->exit_code));
}

/*
** i = 1 to handle the '$'
*/

char	*get_env_var(char *text, int env_var_len)
{
	char	*env_var;
	char	*result;
	char	*exit_code;
	int		i;
	int		j;

	i = 1;
	j = 0;
	env_var = calloc_or_exit(sizeof(char), env_var_len + 1);
	while (text[i] && is_not_exception(text[i], ENV_VAR))
		env_var[j++] = text[i++];
	if (!*env_var)
		result = ft_strdup("$");
	else if (*env_var == '?')
	{
		exit_code = get_exit_code();
		result = ft_strjoin(exit_code, env_var + 1);
		free(exit_code);
	}
	else if (get_env_value(env_var))
		result = ft_strdup(get_env_value(env_var));
	else
		result = ft_strdup("");
	free(env_var);
	return (result);
}

char	**get_env_var_split(char *instruction)
{
	int		nb_env_var;
	int		env_var_len;
	int		count;
	char	quote;
	char	**env_var;

	count = 0;
	quote = 0;
	nb_env_var = get_nb_env_var(instruction);
	env_var = calloc_or_exit(sizeof(char *), nb_env_var + 1);
	while (count < nb_env_var && *instruction)
	{
		quote = check_quote(*instruction, quote);
		if (*instruction == '$' && quote != SGL_QUOTE)
		{
			env_var_len = get_env_var_len(instruction);
			env_var[count] = get_env_var(instruction, env_var_len);
			count++;
		}
		instruction++;
	}
	env_var[count] = 0;
	return (env_var);
}
