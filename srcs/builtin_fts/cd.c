/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:56 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * 3 possible situations:
 * 1) no argument is given => change to HOME
 * 2) - => change to OLDPWD and print PWD
 * 3) relative or absolute path are given => change to path
 * chdir can receive both relative or absolute paths - so smart ✨
 *
 * Error Handling
 * In bash, additional arguments are ignored, if the first argument
 * is correct then the command works properly.
 * In zsh it says "cd: string not in pwd: <first_arg>"
 * In bash, the first time we open the terminal there is no OLDPWD yet,
 * thus calling cd - returns "bash: cd: OLDPWD not set"
 * If we unset HOME and then run cd it returns "bash: cd: HOME not set"
 */

static char	*update_cwd(char *cwd)
{
	if (cwd)
		free(cwd);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	return (cwd);
}

static char	*get_new_cwd(char *cmd_arg)
{
	char	*new_cwd;

	if (!cmd_arg)
	{
		new_cwd = get_env_value("HOME");
		if (!new_cwd)
		{
			error_message(NO_HOME);
			return (NULL);
		}
	}
	else if (ft_strncmp(cmd_arg, "-", 1) == 0)
	{
		new_cwd = get_env_value("OLDPWD");
		if (!new_cwd)
		{
			error_message(NO_OLDPWD);
			return (NULL);
		}
	}
	else
		new_cwd = cmd_arg;
	return (new_cwd);
}

static int	exit_cd(char *cwd, int error_code, int exit_code)
{
	free(cwd);
	if (error_code)
		error_message(error_code);
	return (exit_code);
}

int	cd(t_cmd_table *cmd)
{
	char		*cwd;
	char		*new_cwd;
	int			exit_code;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	new_cwd = get_new_cwd(cmd->cmd_args[0]);
	if (new_cwd == NULL)
		return (exit_cd(cwd, 0, 1));
	exit_code = chdir(new_cwd);
	if (exit_code != 0)
		return (exit_cd(cwd, WRONG_DIR, exit_code));
	set_env_value("OLDPWD", cwd);
	cwd = update_cwd(cwd);
	set_env_value("PWD", cwd);
	if (cmd->cmd_args[0] && ft_strncmp(cmd->cmd_args[0], "-", 1) == 0)
		pwd(cmd);
	return (exit_cd(cwd, 0, 0));
}
