/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:21 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if ((ft_strncmp(cmd_name, "cd", 2) == 0 && ft_strlen(cmd_name) == 2)
		|| ((ft_strncmp(cmd_name, "pwd", 3) == 0
				|| ft_strncmp(cmd_name, "env", 3) == 0)
			&& ft_strlen(cmd_name) == 3)
		|| ((ft_strncmp(cmd_name, "echo", 4) == 0
				|| ft_strncmp(cmd_name, "exit", 4) == 0)
			&& ft_strlen(cmd_name) == 4)
		|| (ft_strncmp(cmd_name, "unset", 5) == 0 && ft_strlen(cmd_name) == 5)
		|| (ft_strncmp(cmd_name, "export", 6) == 0 && ft_strlen(cmd_name) == 6))
		return (1);
	return (0);
}

int	exec_builtin(t_minishell *minishell, t_cmd_table *cmd)
{
	if (ft_strncmp(cmd->cmd_name, "cd", 2) == 0
		&& ft_strlen(cmd->cmd_name) == 2)
		return (cd(cmd));
	if (ft_strncmp(cmd->cmd_name, "pwd", 3) == 0
		&& ft_strlen(cmd->cmd_name) == 3)
		return (pwd(cmd));
	if (ft_strncmp(cmd->cmd_name, "env", 3) == 0
		&& ft_strlen(cmd->cmd_name) == 3)
		return (env(cmd, minishell));
	if (ft_strncmp(cmd->cmd_name, "echo", 4) == 0
		&& ft_strlen(cmd->cmd_name) == 4)
		return (echo(cmd));
	if (ft_strncmp(cmd->cmd_name, "export", 6) == 0
		&& ft_strlen(cmd->cmd_name) == 6)
		return (export(cmd, minishell));
	if (ft_strncmp(cmd->cmd_name, "unset", 5) == 0
		&& ft_strlen(cmd->cmd_name) == 5)
		return (unset(cmd, minishell));
	if (ft_strncmp(cmd->cmd_name, "exit", 4) == 0
		&& ft_strlen(cmd->cmd_name) == 4)
		return (exit_cocoshell(cmd, minishell));
	return (-1);
}
