/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:49:05 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/14 19:15:36 by llecoq           ###   ########.fr       */
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
		dup2(cmd->pipefd[1], STDOUT_FILENO);
	if (cmd->redir.into_file >= EXISTENT)
		if (dup2(cmd->redir.into_file, STDOUT_FILENO) == FAILED)
			close_fds_and_exit(pipex, cmd->pipefd[1], -1);
	close(cmd->pipefd[1]);
}

void	dup_input_redirection(t_pipe *pipex, t_cmd *cmd)
{
	if (cmd->redir.from_heredoc >= EXISTENT)
	{
		dup2(cmd->redir.from_heredoc, STDIN_FILENO);
		close(cmd->redir.from_heredoc);
		close(cmd->pipefd[0]);
		return ;
	}
	if (cmd->redir.from_file >= EXISTENT)
	{
		dup2(cmd->redir.from_file, STDIN_FILENO);
		close(cmd->redir.from_file);
		close(cmd->pipefd[0]);
		return ;
	}
	if (cmd->previous)
	{
		if (dup2(cmd->previous->pipefd[0], STDIN_FILENO) == FAILED)
		{
			close(cmd->pipefd[0]);
			close(cmd->pipefd[1]);
			error_quit(pipex, NULL, 0);
		}
		close(cmd->previous->pipefd[0]);
	}
	else if (cmd->previous == NULL)
		close(cmd->pipefd[0]);
}