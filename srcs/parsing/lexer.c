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
**	lexer
** 
** The lexer (tokeniser) is divided in a few steps.
**	1. Divide the input line in instructions with pipe '|' as a delimiter.
**	2. Then get the number of instructions to init the command tables.
**	3. Then get the command tables content.
**
** 🌴🥥
*/

int	lexer(t_minishell *minishell, char *line)
{
	int		exit_code;

	if (minishell->instructions)
		free_split(minishell->instructions);
	if (minishell->cmd_table)
		free_table(minishell->cmd_table, minishell->nb_cmds);
	if (minishell->child_pids)
		free(minishell->child_pids);
	minishell->instructions = get_instructions(line, PIPE);
	minishell->nb_cmds = get_array_len(minishell->instructions);
	minishell->cmd_table = init_cmd_table(minishell->nb_cmds);
	minishell->child_pids
		= (pid_t *)calloc_or_exit(sizeof(pid_t), minishell->nb_cmds);
	exit_code = get_command_tables(minishell->cmd_table,
			minishell->nb_cmds, minishell->instructions);
	return (exit_code);
}

/*
**	get_command_tables (& two helper functions)
**
**	1. Get the redirections ('>', '<', '>>', '<<' and
**		their following argument).
**	2. Then translate the environement variables - if there's any - in the
**		argument except if the operator is '<<'.
**	2. Rewrite the instruction line without the redirections.
**	3. Translate the environement variables - if there's any - in the
**		instruction line. (Effectively, rewrite the instruction line with
**		the real path of the environement variable.)
**	4. Get the tokens with spaces as delimiter.
**
**	If redir->arg is empty, then treat it as a syntax error that will interupt
**	overall execution of the input line.
**
*/

static bool	is_empty(char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		if (text[i] != SPACE)
			return (false);
		i++;
	}
	return (true);
}

char	*rewrite(char **text, int type)
{
	char	*temp;

	if (type == ENV_VAR)
	{
		temp = rewrite_instruction_with_env_var(*text);
		free(*text);
		*text = temp;
	}
	else if (type == REDIR)
	{
		temp = rewrite_instruction_without_redirs(*text);
		free(*text);
		*text = temp;
	}
	return (*text);
}

static int	get_and_rewrite_redirections(t_cmd_table *cmd_table,
											char **instruction)
{
	int	j;

	cmd_table->redirs = get_redirs(*instruction, cmd_table->nb_redirs);
	j = 0;
	while (j < cmd_table->nb_redirs)
	{
		if (is_empty(cmd_table->redirs[j].arg))
			return (error_and_return(REDIR_NO_ARG, SYNTAX_ERROR));
		if (ft_strchr(cmd_table->redirs[j].arg, '$')
			&& cmd_table->redirs[j].type != OP_DELIMITER)
			cmd_table->redirs[j].arg
				= rewrite(&cmd_table->redirs[j].arg, ENV_VAR);
		j++;
	}
	*instruction = rewrite(instruction, REDIR);
	return (0);
}

int	get_command_tables(t_cmd_table *cmd_table,
								int nb_cmds, char **instructions)
{
	int	i;
	int	error;

	i = 0;
	error = 0;
	while (i < nb_cmds)
	{
		cmd_table[i].nb_redirs = get_nb_redirs(instructions[i]);
		if (cmd_table[i].nb_redirs)
			error = get_and_rewrite_redirections(
					&cmd_table[i], &instructions[i]);
		if (ft_strchr(instructions[i], '$'))
			instructions[i] = rewrite(&instructions[i], ENV_VAR);
		cmd_table[i].nb_tokens = get_nb_tokens(instructions[i], SPACE);
		cmd_table[i].tokens = get_tokens(instructions[i],
				SPACE, cmd_table[i].nb_tokens);
		i++;
	}
	return (error);
}
