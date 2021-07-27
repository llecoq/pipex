/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:13:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/27 18:16:10 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

// A TESTER ZOOOB
static int	check_for_existing_file(t_pipe *pipex, t_cmd *cmd, char *file_name)
{
	char	buff;
	int		fd;
	int		ret;

	fd = open(file_name, O_RDONLY, 0644);
	if (fd > 0)
	{
		ret = read(fd, &buff, 1);
		if (ret == -1)
		{
			// faire fonction close fd ?
			close(cmd->pipefd[0]);
			close(cmd->pipefd[1]);
			close(fd);
			error_quit(pipex, NULL, errno);
		}
		cmd->pipefd[0] = fd; // pas sur
	}
	return (IS_VALID);
}

int	set_redirection(t_pipe *pipex, t_cmd *cmd, t_token *token_list)
{
	int	status;

	status = IS_VALID;
	while (token_list)
	{
		if (token_list->type == IS_FILE && token_list->redir == INPUT_REDIR)
			status = (check_for_existing_file(pipex, cmd, token_list->word));
		else if (token_list->type == IS_FILE)
			status = (create_file(cmd, token_list->word, token_list->redir));
		token_list = token_list->next;
	}
	return (status);
}
