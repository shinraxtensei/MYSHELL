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
** 
**	1. We get the number of redirections to init the struct properly
**	2. We extract the right redir_type to give to the individual redir.
**	3. We save the 'word' following the redir_operator as the argument.
**		That 'word' ends when encountering a SPACE, '<' or '>'.
**
*/

int	get_nb_redirs(char *instructions)
{
	int		count_redirs;
	int		i;
	char	quote;
	char	redir;

	count_redirs = 0;
	i = 0;
	quote = 0;
	redir = 0;
	while (instructions[i])
	{
		quote = check_quote(instructions[i], quote);
		if ((instructions[i] == '<' || instructions[i] == '>') && !quote)
		{
			redir = instructions[i];
			i++;
			if (instructions[i] && instructions[i] == redir)
				i++;
			count_redirs++;
		}
		else
			i++;
	}
	return (count_redirs);
}

static t_redir_type	get_redir_type(const char *instructions, int i)
{
	t_redir_type	redir_type;
	int				redir;

	redir = instructions[i];
	redir_type = 0;
	i++;
	if (instructions[i] && instructions[i] == redir)
	{
		if (redir == '<')
			redir_type = OP_DELIMITER;
		else if (redir == '>')
			redir_type = OP_APPEND;
		i++;
	}
	else
	{
		if (redir == '<')
			redir_type = OP_REDIR_IN;
		else if (redir == '>')
			redir_type = OP_REDIR_OUT;
	}
	return (redir_type);
}

static char	*save_next_word_as_arg(const char *instructions, int i)
{
	char	*arg;
	char	quote;
	int		arg_len;

	arg_len = 0;
	quote = 0;
	while (instructions[i] == SPACE)
		i++;
	while (instructions[i + arg_len]
		&& ((!quote && is_not_exception(instructions[i + arg_len], REDIR))
			|| quote))
	{
		quote = check_quote(instructions[i + arg_len], quote);
		arg_len++;
	}
	arg = calloc_or_exit(sizeof(char), arg_len + 1);
	arg = ft_substr(instructions, i, arg_len);
	return (arg);
}

static int	parse_redir(t_redir *redirs, const char *instructions, int i)
{
	int	len_parse;

	len_parse = 0;
	redirs->type = get_redir_type(instructions, i);
	if (redirs->type == OP_REDIR_IN
		|| redirs->type == OP_REDIR_OUT)
		len_parse += 1;
	else if (redirs->type == OP_DELIMITER
		|| redirs->type == OP_APPEND)
		len_parse += 2;
	redirs->arg = save_next_word_as_arg(instructions, i + len_parse);
	len_parse += ft_strlen(redirs->arg);
	return (len_parse);
}

t_redir	*get_redirs(const char *instructions, int nb_redirs)
{
	t_redir	*redirs;
	int		i;
	int		count;
	char	quote;

	if (!instructions)
		return (NULL);
	redirs = calloc_or_exit(sizeof(t_redir), nb_redirs);
	i = 0;
	count = 0;
	quote = 0;
	while (instructions[i] && count < nb_redirs)
	{
		quote = check_quote(instructions[i], quote);
		if ((instructions[i] == '<' || instructions[i] == '>') && !quote)
		{
			i += parse_redir(&redirs[count], instructions, i);
			count++;
		}
		else
			i++;
	}
	return (redirs);
}
