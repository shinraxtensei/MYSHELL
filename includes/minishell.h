/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:32:18 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "../libft/libft.h"
# include "colors.h"
# include "struct_def.h"
# include "utils.h"
# include "debug.h"
# include "parsing.h"
# include "builtin_fts.h"
# include "executing.h"

/* INITIALIZER */
t_cmd_table	*init_cmd_table(int nb_cmds);
t_minishell	*init_minishell(char **envp);

/* INTERFACE */
char		*get_instructions_line(void);

/* SIGNALS */
void		set_signals(t_status status);
void		set_termcaps(void);

#endif
