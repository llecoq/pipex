/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:04:12 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/18 12:09:51 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	append_redir(t_pipe *pipex, t_token **token)
{
	char	*path_name;
	char	buff;
	int		fd;

	errno = 0;
	path_name = (*token)->word;
	fd = open(path_name, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (fd > 0 && read(fd, &buff, 1) >= 0)
	{
		(*token)->fd = fd;
		return (IS_VALID);
	}
	if (errno)
		error(pipex, path_name, 0);
	return (NONEXISTENT);
}

static int	output_redir(t_pipe *pipex, t_token **token)
{
	char	*path_name;
	char	buff;
	int		fd;

	errno = 0;
	path_name = (*token)->word;
	fd = open(path_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd > 0 && read(fd, &buff, 1) >= 0)
	{
		(*token)->fd = fd;
		return (IS_VALID);
	}
	if (errno)
		error(pipex, path_name, 0);
	return (NONEXISTENT);
}

static int	input_redir(t_pipe *pipex, t_token **token)
{
	char	*path_name;
	int		fd;

	path_name = (*token)->word;
	fd = open(path_name, O_RDONLY, 0777);
	if (fd > 0)
	{
		(*token)->fd = fd;
		return (EXISTENT);
	}
	error(pipex, path_name, 0);
	return (NONEXISTENT);
}

void	set_redirection(t_pipe *pipex, t_token ***token_tab)
{
	t_token *head;
	int		i;

	i = -1;
	while ((*token_tab)[++i])
	{
		head = (*token_tab)[i];
		while ((*token_tab)[i])
		{
			if ((*token_tab)[i]->redir == INPUT_REDIR
				&& input_redir(pipex, &(*token_tab)[i]) == EXISTENT)
				head->cmd = IS_VALID;
			if ((*token_tab)[i]->redir == OUTPUT_REDIR
				&& output_redir(pipex, &(*token_tab)[i]) == IS_VALID)
				head->cmd = IS_VALID;
			if ((*token_tab)[i]->redir == APPEND
				&& append_redir(pipex, &(*token_tab)[i]) == IS_VALID)
				head->cmd = IS_VALID;
			(*token_tab)[i] = (*token_tab)[i]->next;
		}
		(*token_tab)[i] = head;
	}
}
