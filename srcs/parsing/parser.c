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
**
** parser
** 
** The parsing functions will 'recognize' what the token its looking at is.
**		- a command (CMD)
**		- a flag (FLAG)
**		- an argument (WORD)
**	First, it will assign the right type to the token. Then assign the tokens
**	to the right variable that will be fed to the the executor:
**	minishell->cmd_table[i].
**		 					cmd_name
**		 					**flags
**		 					**cmd_args
**
**	ERROR : If there is a NO_EXECUTION error (syntax error from no argument 
**	after a redirection for example), we need to return before assigning tokens
**	that won't have been parsed. (To avoid a segfault.)
**	No need to send a code_message since it will have been handled beforehand
**	in lexer, where the exit_code was defined.
**
** 
*/

int	parse(char *line, t_minishell *minishell)
{
	int		exit_code;
	int		i;

	exit_code = lexer(minishell, line);
	if (exit_code == SYNTAX_ERROR)
	{
		minishell->exit_code = SYNTAX_ERROR;
		return (SYNTAX_ERROR);
	}
	i = 0;
	while (i < minishell->nb_cmds)
	{
		get_tokens_types(minishell->cmd_table[i].tokens,
			minishell->cmd_table[i].nb_tokens);
		assign_tokens(&minishell->cmd_table[i]);
		i++;
	}
	return (exit_code);
}

/*
** get_token_types
**
** 1. This functions cleans up the tokens by removing the closed quotes.
** 2. Then it gets the right token type (CMD, FLAG, WORD) to the given token.
** 	  If it's the first token of the array**, it's a command (since we 
**	  removed the redirections from the line that's being parsed at this
**	  stage, it should always be the case).
** 3. Then wherever the flag is in the line it should be counted as a flag. It
**    needs to start with '-' and be followed by an alphanumerical character.
**    Flags can also look like '--l' or '-llllll' or -lllllllh3' for example.
** 4. Anything else is an argument (WORD).
**
** ⚠️ It also handles the special case of echo which only accepts '-n' or
**	   '-nnnnnnnn' as a flag. The rest should be treated as text.
**
*/

void	get_tokens_types(t_token *tokens, int nb_tokens)
{
	int		i;
	bool	cmd_is_echo;
	int		first_word;

	i = -1;
	cmd_is_echo = false;
	first_word = 0;
	while (++i < nb_tokens)
	{
		if (there_is_quote(tokens[i].text, DBL_QUOTE)
			|| there_is_quote(tokens[i].text, SGL_QUOTE))
			tokens[i].text = ft_strtrim(tokens[i].text, "\"'");
		if (cmd_is_echo)
			tokens[i].type = handle_special_case_echo(tokens, i, &first_word);
		else if (i == 0)
		{
			tokens[i].type = CMD;
			if (ft_strncmp(tokens[i].text, "echo", 4) == 0)
				cmd_is_echo = true;
		}
		else if (tokens[i].text[0] == '-' && ft_isprint(tokens[i].text[1]))
			tokens[i].type = FLAG;
		else
			tokens[i].type = WORD;
	}
}

/*
** get_type_count
**
** This function gets the total number of tokens of the given type
**	WORD, FLAG or CMD.
*/

static int	get_type_count(t_token *tokens, int nb_tokens, t_token_type type)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < nb_tokens)
	{
		if (tokens[i].type == type)
			count++;
		i++;
	}
	return (count);
}

/*
** get_args
**
** This function creates an array** with the token of a given type
**	(WORD or FLAG). It null terminates it with 0.
*/

static char	**get_args(t_token *tokens, int nb_tokens, t_token_type arg_type)
{
	int		i;
	int		j;
	int		nb_args;
	char	**args;

	i = 0;
	j = 0;
	nb_args = get_type_count(tokens, nb_tokens, arg_type);
	args = calloc_or_exit(sizeof(char *), nb_args + 1);
	while (i < nb_tokens)
	{
		if (tokens[i].type == arg_type)
			args[j++] = tokens[i].text;
		i++;
	}
	args[j] = 0;
	return (args);
}

/*
** assign_tokens
**
** This function puts the tokens in the appropriate variable to be fed
** to the executor.
** ⚠️ It also removes the closed quotes from the redirections.
*/

void	assign_tokens(t_cmd_table *cmd_table)
{
	int	i;

	i = 0;
	while (i < cmd_table->nb_redirs)
	{
		if (there_is_quote(cmd_table->redirs[i].arg, DBL_QUOTE)
			|| there_is_quote(cmd_table->redirs[i].arg, SGL_QUOTE))
		{
			cmd_table->redirs[i].quote = true;
			cmd_table->redirs[i].arg = remove_quotes(cmd_table->redirs[i].arg);
		}
		i++;
	}
	cmd_table->cmd_name = cmd_table->tokens[0].text;
	cmd_table->flags = get_args(cmd_table->tokens, cmd_table->nb_tokens, FLAG);
	cmd_table->cmd_args = get_args(
			cmd_table->tokens, cmd_table->nb_tokens, WORD);
}
