/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:13:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/23 09:23:21 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	create_file(t_cmd *cmd, char *file_name, int redir_type)
{
	if (redir_type == APPEND)
		cmd->redir.into_file
			= open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redir_type == TRUNC)
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

static int	check_for_existing_file(t_cmd *cmd, char *file_name)
{
	int		fd;

	fd = open(file_name, O_RDONLY);
	if (fd > 0)
	{
		cmd->redir.from_file = fd;
		return (IS_VALID);
	}
	return (errno);
}

static void	search_for_output_redir(t_token *token_list, t_cmd *cmd)
{
	if (token_list->redir == APPEND || token_list->redir == TRUNC)
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
			error_quit(pipex, file_name, SYSCALL_ERROR);
		token_list = token_list->next;
	}
}
