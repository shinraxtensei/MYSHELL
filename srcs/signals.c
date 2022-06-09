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
** 🦕🌴
**
**	set_signals
**
**	1. CTRL-C
**		Interrupt the current processes in minishell but NOT exit minishell.
**		Will print a newline in main process and ^C\n in child process.
**	2. CTRL-\
**		Do nothing. (in process) "Quit: 3\n"
**	3. CTRL-D (EOF)
**		Already works. Nothing to do.
**
**	Since signals react differently in the main/parent process nand in the child
**	process, we need to handle both case by resetting constantly the signals
**	according to where we are in the processes.
**
** 🌴🥥
*/

static void	sigint_handler(int sig_num)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	if (sig_num == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDIN_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		minishell->exit_code = 1;
	}
	return ;
}

static void	signal_handler_child(int sig_num)
{
	t_minishell	*minishell;

	minishell = get_minishell(NULL);
	if (sig_num == SIGINT)
	{
		minishell->exit_code = EXIT_SIGINT;
		ft_putstr_fd("^C\n", STDERR_FILENO);
	}
	if (sig_num == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
		minishell->exit_code = EXIT_SIGQUIT;
	}
	return ;
}

void	set_signals(t_status status)
{
	if (status == CHILD_PROCESS)
	{
		if (signal(SIGINT, signal_handler_child) == SIG_ERR)
			error_and_exit(SIGNAL_ERROR);
		if (signal(SIGQUIT, signal_handler_child) == SIG_ERR)
			error_and_exit(SIGNAL_ERROR);
	}
	else
	{
		if (signal(SIGINT, sigint_handler) == SIG_ERR)
			error_and_exit(SIGNAL_ERROR);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			error_and_exit(SIGNAL_ERROR);
	}
}

/*
**	Termcaps
**
** (Text is extracted from @gleal very precious README on this project
**	and the termcaps documentation)
**
**	Termcaps stands for terminal capabilities.
**
**		struct termios {
**			tcflag_t c_iflag;
**			tcflag_t c_oflag;
**			tcflag_t c_cflag;
**			tcflag_t c_lflag;
**			cc_t c_cc[NCCS];
**			speed_t c_ispeed;
**			speed_t c_ospeed;
**		};
**
**			1.	int tcgetattr(int fd, struct termios *termios_p);
**		we check if there is a terminfo database
**		(database with all terminal capabilities) for the TERM environment
**		variable in our envp array and load the functions internally, so that
**		the tgetstr function works.
**
**			2.	int tcsetattr(int fd, int optional_actions,
**					   			 const struct termios *termios_p);
**		to check and save in a struct and tputs to activate the 
**		following capabilities:
**
**		ECHOCTL
**            (not in POSIX) If ECHO is also set, terminal special
**             characters other than TAB, NL, START, and STOP are echoed
**             as ^X, where X is the character with ASCII code 0x40
**             greater than the special character.  For example,
**             character sad (BS) is echoed as ^H.
** 			~ECHOCTL : Turns off the standard echo of "CTRL + KEY"
**		TCSANOW
**             the change occurs immediately.
**
*/

void	set_termcaps(void)
{
	struct termios	termcaps;

	if (tcgetattr(0, &termcaps) == -1)
		error_and_exit(TERMCAP_ERROR);
	termcaps.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &termcaps) == -1)
		error_and_exit(TERMCAP_ERROR);
}
