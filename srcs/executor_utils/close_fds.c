/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:55:48 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/14 17:55:51 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	close_unused_fds(t_cmd *cmd)
{
	t_cmd	*next_cmd;

	next_cmd = NULL;
	if (cmd->next)
		next_cmd = cmd->next->next;
	while (next_cmd)
	{
		close(next_cmd->pipefd[0]);
		close(next_cmd->pipefd[1]);
		next_cmd = next_cmd->next;
	}
}
