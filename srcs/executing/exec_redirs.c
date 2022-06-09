/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:31:13 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Delimiters and Here docs:
 * Create a temporary file and set is_infile_tmp to 1, so that we know we need
 * to remove it when closing it.
 * After writing to the temporary file, we close it and open it again, so that
 * the offset goes back to the beginning of the file (else it's pointing at the
 * end of the file and it won't print anything!)
 *
 * What is the best strategy to create a temporary file?
 * There are two problems I need to take into consideration:
 * 1) There's a file with the same name and in the same directory as my
 *    temporary file. Solution: Create it in a directory which is hard to find,
 *    such as /tmp.
 * 2) File needs to have a unique name, else if I run minishell twice at the
 *    same time and call cat << . in both, it will be writing to the same file.
 *    Solution: add tty name to the file name.
 */

/*
** If an environement variable is called inside a heredoc, it is expanded.
**	/!\ Unless the delimiter is in between quotes. /!\
*/
static void	exec_redirs_heredoc(t_cmd_table *cmd, int i)
{
	char	*line;

	cmd->infile_tmp = ft_strjoin("/tmp/1337", ft_itoa(rand() % 100));
	cmd->is_infile_tmp = 1;
	cmd->fd_in = open(cmd->infile_tmp, O_RDWR | O_CREAT | O_APPEND, 00755);
	if (cmd->fd_in == -1)
		error_and_exit(OPEN_FAIL);
	while (1)
	{
		line = readline("> ");
		if (!(line && !ft_strlen(line)) && (!line
				|| ft_strncmp(line, cmd->redirs[i].arg, ft_strlen(line)) == 0))
			break ;
		if (!cmd->redirs[i].quote)
			line = rewrite(&line, ENV_VAR);
		write(cmd->fd_in, line, ft_strlen(line));
		write(cmd->fd_in, "\n", 1);
		free(line);
		line = NULL;
	}
	free(line);
	close(cmd->fd_in);
	cmd->fd_in = open(cmd->infile_tmp, O_RDWR, 00755);
}

static int	exec_redirs_in(t_cmd_table *cmd, int i)
{
	if (cmd->fd_in != 0 && cmd->is_infile_tmp)
	{
		if (unlink(cmd->infile_tmp) == -1)
			error_and_exit(UNLINK_FAIL);
		free(cmd->infile_tmp);
		cmd->infile_tmp = NULL;
		cmd->is_infile_tmp = 0;
	}
	if (cmd->fd_in != 0 && close(cmd->fd_in) == -1)
		error_and_exit(CLOSE_FAIL);
	cmd->fd_in = open(cmd->redirs[i].arg, O_RDWR, 00755);
	if (cmd->redirs[i].type == OP_REDIR_IN && cmd->fd_in == -1)
		return (error_and_return(OPEN_FAIL, 1));
	else if (cmd->redirs[i].type == OP_DELIMITER)
		exec_redirs_heredoc(cmd, i);
	return (0);
}

static void	exec_redirs_out(t_cmd_table *cmd, int i)
{
	if (cmd->fd_out != 1 && close(cmd->fd_out) == -1)
		error_and_exit(CLOSE_FAIL);
	if (cmd->redirs[i].type == OP_APPEND)
		cmd->fd_out = open(cmd->redirs[i].arg,
				O_RDWR | O_CREAT | O_APPEND, 00755);
	else
		cmd->fd_out = open(cmd->redirs[i].arg,
				O_RDWR | O_CREAT | O_TRUNC, 00755);
	if (cmd->fd_out == -1)
		error_and_exit(OPEN_FAIL);
}

/*
 * Error Handling
 * - if close returns an error, we exit
 * - if open returns an error in a redirection out or in a here doc we exit,
 *   since that means it somehow failed to create the file
 * - if open returns an error in a redirection in, we display an error message
 *   and return to go to next command, as it might be because the file doesn't
 *   exist (pretty common user error)
 */
int	exec_redirs(t_minishell *minishell, t_cmd_table *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_redirs)
	{
		if (cmd->redirs[i].type == OP_REDIR_IN
			|| cmd->redirs[i].type == OP_DELIMITER)
		{
			if (exec_redirs_in(cmd, i))
			{
				minishell->exit_code = 1;
				return (1);
			}
		}
		else if (cmd->redirs[i].type == OP_REDIR_OUT
			|| cmd->redirs[i].type == OP_APPEND)
			exec_redirs_out(cmd, i);
		i++;
	}
	return (0);
}
