/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:13:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/30 10:19:01 by llecoq           ###   ########.fr       */
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

static void	search_for_redir_type(t_token *token, t_cmd *cmd)
{
	if (token->redir == OUTPUT_REDIR || token->redir == APPEND)
	{
		cmd->redir.file = 1;
		cmd->redir.out = 0;
	}
}

void	create_redirection(t_pipe *pipex, t_cmd *cmd, t_token *token_list)
{
	int		status;
	char	*file_name;

	status = IS_VALID;
	while (token_list)
	{
		search_for_redir_type(token_list, cmd);
		file_name = token_list->word;
		if (token_list->type == IS_FILE && token_list->redir == INPUT_REDIR)
			status = check_for_existing_file(cmd, file_name);
		else if (token_list->type == IS_FILE && token_list->redir != INPUT_REDIR)
			status = create_file(cmd, file_name, token_list->redir);
		if (status >= IS_NOT_VALID)
			error_quit(pipex, file_name, 0);
		token_list = token_list->next;
	}
	if (cmd->next)
		cmd->next->pipefd[0] = cmd->pipefd[1];
	// // if (token_list->previous)
	// 	dup2(cmd->pipefd[1], 1);// dup2 close les fd rediriges ? lire man
	// // utiliser dup a la place peut etre ?
	// // attention a proteger dup2 MAN
	// if (cmd->next)
	// {
	// 	cmd->next->pipefd[1] = cmd->pipefd[0];
	// 	close(cmd->next->pipefd[1]);
	// }
	// if (cmd->previous)
	// 	dup2(cmd->pipefd[1], 0);
	// close(cmd->pipefd[0]);
	// close(cmd->pipefd[1]);
}
