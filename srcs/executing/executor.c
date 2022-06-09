/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:10 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * 🥥🌴 EXECUTOR 🥥🌴
 *
 * 1. Pipes and Redirections (more in exec_redirs.c)
 * An fd which is not STDIN nor STDOUT will be closed as soon as it's not needed
 * - if there are redirections, the pipe's writing end is closed
 * - if there are multiple redirections, the previous file is closed before the
 *   next one is opened
 * - in this way, no matter how many redirections and/or pipes there might be,
 *	 the fd never goes above 5
 * - if something happens we're out with exit_code 1
 *
 * 2. If there's no command, we're out with exit_code 0
 * 
 * 3. If it's a built-in function and a single instruction, the command is ran
 * in the minishell process. The exit code is updated with what the command
 * returns and that is returned to the main.
 *
 * 4. Executing in a Child Process
 * We need to create a child process, which will execute the command. In the
 * parent process, we wait for all the child processes to execute and return the
 * right exit code.
 * - a command needs to start executing before the previous one is finished
 *	 for e.g: sleep 5 | ls -> result of ls is printed before sleep finishes
 * - once a command finishes execution, we need to close the writing end of the
 *	 pipe, else if the following command expects input (such as cat or bc) it
 *	 will keep on waiting forever
 * - we need to return the exit code from the last command in the line, not the
 *	 latest to finish execution. for e.g: sleep 5 | las -> returns 127 as las
 *	 does not exist, even though sleep 5 finishes executing later. For that we
 *	 wait and store the exit codes in order.
 */

/*
 * Error Handling: if pipe returns an error, we exit
 */
static void	open_pipe(t_minishell *minishell, int i)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_and_exit(PIPE_FAIL);
	minishell->cmd_table[i].fd_out = fd[1];
	minishell->cmd_table[i + 1].fd_in = fd[0];
}

/*
 * If someone tried to open a file that doesn't exist, fd_in = -1
 * That is a common error so we do not want to exit
 */
static void	close_for_next_cmd(t_cmd_table *cmd)
{
	if (cmd->fd_in != 0 && cmd->is_infile_tmp)
	{
		if (unlink(cmd->infile_tmp) == -1)
			error_and_exit(UNLINK_FAIL);
		free(cmd->infile_tmp);
		cmd->infile_tmp = NULL;
		cmd->is_infile_tmp = 0;
	}
	if (cmd->fd_in != 0 && cmd->fd_in != -1 && close(cmd->fd_in) == -1)
		error_and_exit(CLOSE_FAIL);
	if (cmd->fd_out != 1 && close(cmd->fd_out) == -1)
		error_and_exit(CLOSE_FAIL);
}

static void	exec_in_child(t_minishell *minishell, int i)
{
	minishell->child_pids[i] = fork();
	if (minishell->child_pids[i] == -1)
		error_and_exit(FORK_FAIL);
	set_signals(CHILD_PROCESS);
	if (minishell->child_pids[i] == 0)
	{
		if (is_builtin(minishell->cmd_table[i].cmd_name))
			exit(exec_builtin(minishell, &minishell->cmd_table[i]));
		exec_system(minishell, &minishell->cmd_table[i]);
	}
}

static void	wait_and_get_exit_code(t_minishell *minishell)
{
	int	i;
	int	*exit_codes;
	int	status;

	i = 0;
	exit_codes = (int *)calloc_or_exit(sizeof(int), minishell->nb_cmds);
	while (i < minishell->nb_cmds)
	{
		waitpid(minishell->child_pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_codes[i] = WEXITSTATUS(status);
		i++;
	}
	if (minishell->exit_code != EXIT_SIGQUIT
		&& minishell->exit_code != EXIT_SIGINT)
		minishell->exit_code = exit_codes[minishell->nb_cmds - 1];
	free(exit_codes);
}

int	execute(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->nb_cmds)
	{
		if (i + 1 < minishell->nb_cmds)
			open_pipe(minishell, i);
		if ((exec_redirs(minishell, &minishell->cmd_table[i]))
			|| !minishell->cmd_table[i].cmd_name)
		{
			close_for_next_cmd(&minishell->cmd_table[i++]);
			continue ;
		}
		if (is_builtin(minishell->cmd_table[i].cmd_name)
			&& minishell->nb_cmds == 1)
			return (minishell->exit_code = exec_builtin(minishell,
					&minishell->cmd_table[i]));
		exec_in_child(minishell, i);
		close_for_next_cmd(&minishell->cmd_table[i++]);
	}
	wait_and_get_exit_code(minishell);
	set_signals(RESET);
	return (minishell->exit_code);
}
