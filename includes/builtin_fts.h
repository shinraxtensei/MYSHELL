/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fts.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:32:31 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FTS_H
# define BUILTIN_FTS_H

/* CD - Change Directory */
int	cd(t_cmd_table *cmd);

/* PWD - Print Working Directory */
int	pwd(t_cmd_table *cmd);

/* ECHO */
int	echo(t_cmd_table *cmd);

/* ENV - Print all environment variables */
int	env(t_cmd_table *cmd, t_minishell *minishell);

/* EXPORT */
int	export(t_cmd_table *cmd, t_minishell *minishell);

/* UNSET */
int	unset(t_cmd_table *cmd, t_minishell *minishell);

/* EXIT */
int	exit_cocoshell(t_cmd_table *cmd, t_minishell *minishell);

#endif
