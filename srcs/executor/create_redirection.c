/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:13:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/30 12:20:40 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	create_file(t_cmd *cmd, char *file_name, int redir_type)
{
	if (redir_type == APPEND)
		cmd->pipefd[1] = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redir_type == OUTPUT_REDIR)
		cmd->pipefd[1] = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->pipefd[1] == -1)
	{
		close(cmd->pipefd[1]);
		close(cmd->pipefd[0]);
		if (errno == EBADF)
			errno = ENOENT;
		return (errno);
	}
	return (IS_VALID);
}

static int	check_for_existing_file(t_cmd *cmd, char *file_name)
{
	char	buff;
	int		fd;
	int		ret;

	fd = open(file_name, O_RDONLY);
	if (fd > 0)
	{
		ret = read(fd, &buff, 1);
		if (ret == -1)
		{
			// faire fonction close fd ?
			close(cmd->pipefd[0]);
			close(cmd->pipefd[1]);
			close(fd);
			return (errno);
		}
		cmd->pipefd[0] = fd; // pas sur
		return (IS_VALID);
	}
	return (errno);
}

static void	search_for_output_redir(t_token *token_list, t_cmd *cmd)
{
	while (token_list)
	{
		if (token_list->redir == APPEND || token_list->redir == OUTPUT_REDIR)
		{
			cmd->redir.into_file = EXISTENT;
			return ;
		}
		token_list = token_list->next;
	}
	if (token_list->redir == PIPE)
		cmd->redir.into_stdin = EXISTENT;
}

static void	search_for_input_redir(t_token *token_list, t_cmd *cmd)
{
	while (token_list)
	{
		if (token_list->type == HEREDOC || token_list->redir == INPUT_REDIR)
		{
			cmd->redir.from_file = EXISTENT;
			return ;
		}
		token_list = token_list->next;
	}
}

// static void	connect_to_next_pipe(t_cmd *cmd)
// {
// 	if (cmd->next)
// 		cmd->next->pipefd[0] = cmd->pipefd[1];
// 	// if (cmd->previous)
// 	// 	cmd->previous->pipefd[1] = cmd->pipefd[0];
// }

void	create_redirection(t_pipe *pipex, t_cmd *cmd, t_token *token_list)
{
	int		status;
	char	*file_name;

	search_for_input_redir(token_list, cmd);
	search_for_output_redir(token_list, cmd);
	status = IS_VALID;
	while (token_list)
	{
		file_name = token_list->word;
		if (token_list->type == IS_FILE && token_list->redir == INPUT_REDIR)
			status = check_for_existing_file(cmd, file_name);
		else if (token_list->type == IS_FILE && token_list->redir != INPUT_REDIR)
			status = create_file(cmd, file_name, token_list->redir);
		if (status >= IS_NOT_VALID)
			error_quit(pipex, file_name, 0);
		token_list = token_list->next;
	}
	// connect_to_next_pipe(cmd);
}
