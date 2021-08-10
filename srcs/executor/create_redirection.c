/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:13:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/10 14:05:54 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	create_file(t_cmd *cmd, char *file_name, int redir_type)
{
	if (redir_type == APPEND)
		cmd->redir.into_file
			= open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redir_type == OUTPUT_REDIR)
		cmd->redir.into_file
			= open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->redir.into_file == FAILED)
	{
		close(cmd->redir.into_file);
		if (errno == EBADF)
			errno = ENOENT;
		return (errno);
	}
	return (IS_VALID);
}

int	check_for_existing_file(t_cmd *cmd, char *file_name)
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
			close(fd);
			return (errno);
		}
		close(fd);
		cmd->redir.from_file = file_name; // ne marche pas pour heredoc
		return (IS_VALID);
	}
	return (errno);
}

void	search_for_output_redir(t_token *token_list, t_cmd *cmd)
{
	if (token_list->redir == APPEND || token_list->redir == OUTPUT_REDIR)
		cmd->redir.into_file = EXISTENT;
	if (token_list->type == IS_CMD && token_list->redir == PIPE)
		cmd->redir.into_stdin = EXISTENT;
}

void	create_redirection(t_pipe *pipex, t_cmd *cmd, t_token *token_list)
{
	int		redir_status;
	char	*file_name;

	redir_status = IS_VALID;
	while (token_list)
	{
		search_for_output_redir(token_list, cmd);
		file_name = token_list->word;
		if (token_list->type == IS_FILE && token_list->redir == INPUT_REDIR)
			redir_status = check_for_existing_file(cmd, file_name);
		else if (token_list->type == IS_FILE)
			redir_status = create_file(cmd, file_name, token_list->redir);
		if (redir_status >= IS_NOT_VALID)
			error_quit(pipex, file_name, 0);
		token_list = token_list->next;
	}
}
