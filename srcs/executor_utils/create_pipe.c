/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 20:07:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/14 20:18:40 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	create_pipe(t_pipe *pipex, t_cmd *cmd)
{
	if (pipe(cmd->pipefd) == FAILED)
	{
		if (cmd->previous)
		{
			close(cmd->previous->pipefd[0]);
			close(cmd->previous->pipefd[1]);
		}
		error_quit(pipex, NULL, 0);
	}
}
