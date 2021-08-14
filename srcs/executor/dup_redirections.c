/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:49:05 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/14 20:18:23 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	close_fds_and_exit(t_pipe *pipex, int fd_1, int fd_2)
{
	if (fd_1 >= EXISTENT)
		close(fd_1);
	if (fd_2 >= EXISTENT)
		close(fd_2);
	error_quit(pipex, NULL, 0);
}

void	dup_output_redirection(t_pipe *pipex, t_cmd *cmd)
{
	if (cmd->redir.into_stdin == EXISTENT)
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == FAILED)
			close_fds_and_exit(pipex, cmd->pipefd[1], -1);
	if (cmd->redir.into_file >= EXISTENT)
		if (dup2(cmd->redir.into_file, STDOUT_FILENO) == FAILED)
			close_fds_and_exit(pipex, cmd->pipefd[1], -1);
	close(cmd->pipefd[1]);
}

static void	redir_input(t_pipe *pipex, t_cmd *cmd, int redir_type)
{
	int	fd;

	fd = -1;
	if (redir_type == FROM_HEREDOC)
		fd = cmd->redir.from_heredoc;
	else if (redir_type == FROM_FILE)
		fd = cmd->redir.from_file;
	else if (redir_type == FROM_STDIN)
		fd = cmd->previous->pipefd[0];
	if (dup2(fd, STDIN_FILENO) == FAILED)
	{
		close(cmd->pipefd[0]);
		close(cmd->pipefd[1]);
		error_quit(pipex, NULL, 0);
	}
	close(fd);
	close(cmd->pipefd[0]);
}

void	dup_input_redirection(t_pipe *pipex, t_cmd *cmd)
{
	if (cmd->redir.from_heredoc >= EXISTENT)
		redir_input(pipex, cmd, FROM_HEREDOC);
	if (cmd->redir.from_file >= EXISTENT)
		redir_input(pipex, cmd, FROM_FILE);
	if (cmd->previous)
		redir_input(pipex, cmd, FROM_STDIN);
}
