/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:29:17 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char				*line;
	t_minishell			*minishell;
	int					exit_code;

	(void)argv;
	set_termcaps();
	if (argc > 1)
		printf("minishell: too many arguments\n");
	minishell = init_minishell(envp);
	set_signals(INIT);
	while (1)
	{
		line = get_instructions_line();
		if (!line)
			break ;
		exit_code = parse(line, minishell);
		free(line);
		if (exit_code != SYNTAX_ERROR && minishell->nb_cmds)
			exit_code = execute(minishell);
	}
	free_minishell(minishell);
	return (exit_code);
}
