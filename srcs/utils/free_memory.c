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
** Frees the various allocated pieces of memory in the
**	minishell struct.
*/

void	free_minishell(t_minishell *minishell)
{
	rl_clear_history();
	if (minishell->instructions)
		free_split(minishell->instructions);
	if (minishell->cmd_table)
		free_table(minishell->cmd_table, minishell->nb_cmds);
	if (minishell->env)
		ft_lstclear(&minishell->env, &del_env_content);
	if (minishell->env_paths)
		free_split(minishell->env_paths);
	if (minishell->child_pids)
		free(minishell->child_pids);
	if (minishell)
		free(minishell);
	return ;
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_table(t_cmd_table *cmd_table, int nb_cmds)
{
	int	i;

	i = 0;
	while (i < nb_cmds)
	{
		if (cmd_table[i].redirs)
			free_redirs(cmd_table[i].redirs, cmd_table[i].nb_redirs);
		if (cmd_table[i].tokens)
			free_tokens(cmd_table[i].tokens, cmd_table[i].nb_tokens);
		if (cmd_table[i].flags)
			free(cmd_table[i].flags);
		if (cmd_table[i].cmd_args)
			free(cmd_table[i].cmd_args);
		if (cmd_table[i].cmd_path)
			free(cmd_table[i].cmd_path);
		if (cmd_table[i].infile_tmp)
			free(cmd_table[i].infile_tmp);
		if (cmd_table[i].fd_in != 0)
			close(cmd_table[i].fd_in);
		if (cmd_table[i].fd_out != 1)
			close(cmd_table[i].fd_out);
		i++;
	}
	free(cmd_table);
}

void	free_tokens(t_token *tokens, int nb_tokens)
{
	int	i;

	i = 0;
	while (i < nb_tokens)
	{
		free(tokens[i].text);
		i++;
	}
	free(tokens);
}

void	free_redirs(t_redir *redirs, int nb_redirs)
{
	int	i;

	i = 0;
	while (i < nb_redirs)
	{
		free(redirs[i].arg);
		i++;
	}
	free(redirs);
}
