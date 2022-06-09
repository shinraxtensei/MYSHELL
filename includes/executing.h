/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:32:21 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

/* EXECUTOR */
int		execute(t_minishell *minishell);

/* EXECUTE REDIRECTIONS */
int		exec_redirs(t_minishell *minishell, t_cmd_table *cmd);

/* EXECUTE BUILTIN COMMANDS */
int		is_builtin(char *cmd_name);
int		exec_builtin(t_minishell *minishell, t_cmd_table *cmd);

/* EXECUTE SYSTEM COMMANDS */
int		valid_command(t_minishell *minishell, t_cmd_table *cmd);
void	exec_system(t_minishell *minishell, t_cmd_table *cmd);

/* ENVIRONEMENT PATHS */
void	get_cmd_paths(t_minishell *minishell);
char	**finish_paths_by_slash(char **raw_paths);

#endif
