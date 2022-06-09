/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:41 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * - Negative numbers are perceived as flags by our parsing, so in this case I
 *   use the tokens (name + flags + arguments) instead of the arguments
 * - Plus, if we run 'exit -n 2' exit perceives '-n' as an argument (thus saying
 *   we need numeric arguments, so my approach is consistent with this behaviour
 * - Exit prints 'exit' even in case of error
 * - When there's multiple arguments, if the first argument is non-numeric, the
 *   non-numeric error wins, if the first argument is numeric (even if the next
 *   one isn't) the too many arguments error wins
 * - It somehow converts numbers < 0 or > 256 to an unsigned char automatically
 * - I know it's silly to return after exit, but I kinda had to return
 *   something... better something that kinda makes sense.
 */
int	exit_cocoshell(t_cmd_table *cmd, t_minishell *minishell)
{
	int	exit_code;

	ft_putstr_fd("exit\n", cmd->fd_out);
	if (cmd->nb_tokens >= 2 && !str_is_number(cmd->tokens[1].text))
		error_and_exit(NON_NUM_ARG);
	if (cmd->nb_tokens > 2)
		return (error_and_return(TOO_MANY_ARGS, 1));
	if (cmd->nb_tokens == 2)
		minishell->exit_code = ft_atoi(cmd->tokens[1].text);
	exit_code = minishell->exit_code;
	free_minishell(minishell);
	exit(exit_code);
	return (exit_code);
}
