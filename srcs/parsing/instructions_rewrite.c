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
** rewrite_instructions
**
** Those functions serve two purposes
**
**	1. rewrite the original instruction parsed from the input
**		with the real path of environement variables.
**	2. erase the redirections from the parsed instructions before
**		tokenisation.
**	For both, we first calculate the final length of the rewritten
**	instruction line. Then we copy with the added or removed content.
**
** 🌴🥥
*/

static int	get_len_instruction(char *instruction, char **env_var, char quote)
{
	int		len;
	int		i;
	int		count;

	len = 0;
	i = 0;
	count = 0;
	while (instruction[i])
	{
		quote = check_quote(instruction[i], quote);
		if (instruction[i] == '$' && quote != SGL_QUOTE)
		{
			i++;
			len = len + ft_strlen(env_var[count++]);
			while (instruction[i] && is_not_exception(instruction[i], ENV_VAR))
				i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

static char	*write_env_var_to_temp(char *instruction, char **env_var,
										int len_instruction)
{
	char	*temp;
	char	quote;
	int		c;
	int		i;
	int		j;

	temp = calloc_or_exit(sizeof(char), len_instruction + 1);
	quote = 0;
	c = 0;
	i = 0;
	j = 0;
	while (instruction[i])
	{
		quote = check_quote(*instruction, quote);
		if (instruction[i] == '$' && quote != SGL_QUOTE && env_var[c])
		{
			j += ft_strlcpy(temp + j, env_var[c], ft_strlen(env_var[c]) + 1);
			i = i + get_env_var_len(instruction + i);
			c++;
		}
		else
			temp[j++] = instruction[i++];
	}
	temp[j] = 0;
	return (temp);
}

char	*rewrite_instruction_with_env_var(char *instruction)
{
	char	*temp;
	char	**env_var;
	int		len_instruction;
	char	quote;

	quote = 0;
	env_var = get_env_var_split(instruction);
	len_instruction = get_len_instruction(instruction, env_var, quote);
	temp = write_env_var_to_temp(instruction, env_var, len_instruction);
	free_split(env_var);
	return (temp);
}

static char	*erase_redirs(char *instruction, int len)
{
	char	*temp;
	char	quote;
	int		i;
	int		j;

	temp = calloc_or_exit(sizeof(char), len + 1);
	quote = 0;
	i = 0;
	j = 0;
	while (instruction[i])
	{
		quote = check_quote(instruction[i], quote);
		if ((instruction[i] == '<' || instruction[i] == '>') && !quote)
			i += pass_redir(instruction + i);
		else
			temp[j++] = instruction[i++];
	}
	return (temp);
}

char	*rewrite_instruction_without_redirs(char *instruction)
{
	char	*temp;
	char	quote;
	int		len;
	int		i;

	quote = 0;
	len = 0;
	i = 0;
	while (instruction[i + len])
	{
		quote = check_quote(instruction[i + len], quote);
		if ((instruction[i + len] == '<' || instruction[i + len] == '>')
			&& !quote)
			i += pass_redir(instruction + i + len);
		else
			len++;
	}
	temp = erase_redirs(instruction, len);
	return (temp);
}
