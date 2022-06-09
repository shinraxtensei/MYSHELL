/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:17 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If command is a relative path to an executable (there's a '/')
** that path is stored as the command path.
** 
** (Else) the command is the name of a binary file, and we need to find it
** Checks if the command exists on each path and is executable
** Access function: F_OK - command exists
**                  X_OK - is executable
** If yes, the path is stored in that cmd_table, ready to be used.
*/

int	valid_command(t_minishell *minishell, t_cmd_table *cmd)
{
	int	i;

	if (ft_strchr(cmd->cmd_name, '/'))
	{
		if (access(cmd->cmd_name, F_OK) == 0
			&& access(cmd->cmd_name, X_OK) == 0)
		{
			cmd->cmd_path = ft_strdup(cmd->cmd_name);
			return (0);
		}
		return (FILE_NOT_FOUND);
	}
	get_cmd_paths(minishell);
	i = 0;
	while (minishell->env_paths[i])
	{
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		cmd->cmd_path = ft_strjoin(minishell->env_paths[i], cmd->cmd_name);
		if (access(cmd->cmd_path, F_OK) == 0
			&& access(cmd->cmd_path, X_OK) == 0)
			return (0);
		i++;
	}
	return (CMD_NOT_FOUND);
}

static char	**build_execve_args(t_cmd_table *cmd)
{
	char	**execve_args;
	int		i;

	execve_args = (char **)calloc_or_exit(sizeof(char *), cmd->nb_tokens + 1);
	i = 0;
	while (i < cmd->nb_tokens)
	{
		execve_args[i] = ft_strdup(cmd->tokens[i].text);
		i++;
	}
	execve_args[i] = NULL;
	return (execve_args);
}

/*
 * na_len = name_len , va_len = value_len
 * I'm sorry for the cryptic names, but... norminette
 */
static char	**build_execve_envp(t_minishell *minishell)
{
	char	**envp;
	int		i;
	int		na_len;
	int		va_len;

	envp = (char **)calloc_or_exit(sizeof(char *),
			ft_lstsize(minishell->env) + 1);
	i = 0;
	while (minishell->env)
	{
		na_len = ft_strlen(get_env_lst_name(minishell->env));
		va_len = 0;
		if (get_env_lst_value(minishell->env))
			va_len = ft_strlen(get_env_lst_value(minishell->env));
		envp[i] = (char *)calloc_or_exit(sizeof(char), na_len + va_len + 2);
		ft_strlcpy(envp[i], get_env_lst_name(minishell->env), na_len + 1);
		envp[i][na_len] = '=';
		if (va_len != 0)
			ft_strlcat(envp[i], get_env_lst_value(minishell->env),
				na_len + va_len + 2);
		minishell->env = minishell->env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	exec_system(t_minishell *minishell, t_cmd_table *cmd)
{
	char	**execve_args;
	char	**envp;
	int		exit_code;

	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	exit_code = valid_command(minishell, cmd);
	if (exit_code == 0)
	{
		execve_args = build_execve_args(cmd);
		envp = build_execve_envp(minishell);
		execve(cmd->cmd_path, execve_args, envp);
		free_split(execve_args);
		free(envp);
	}
	error_and_exit(exit_code);
}
