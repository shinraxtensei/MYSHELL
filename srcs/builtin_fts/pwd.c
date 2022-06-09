/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:34 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Error Handling
 * In bash, arguments are ignored.
 * In zsh it says "pwd: too many arguments".
 */

int	pwd(t_cmd_table *cmd)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	ft_putstr_fd(cwd, cmd->fd_out);
	write(cmd->fd_out, "\n", 1);
	free(cwd);
	return (0);
}
