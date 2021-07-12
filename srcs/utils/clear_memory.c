/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:02:57 by user42            #+#    #+#             */
/*   Updated: 2021/07/10 15:37:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	free_cmd_list(t_token **lst)
{
	t_token		*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->word);
		free((*lst));
		(*lst) = NULL;
		*lst = tmp;
	}
	*lst = NULL;
}

void	free_cmd_tab(t_pipe *pipex)
{
	int	i;

	i = -1;
	while (pipex->cmd[++i])
	{
		free_cmd_list(&pipex->cmd[i]);
		free(pipex->cmd[i]);
		pipex->cmd[i] = NULL;
	}
	free(pipex->cmd);
	pipex->cmd = NULL;
}

void	clear_memory(t_pipe *pipex)
{
	if (pipex->path)
		ft_lstclear(&pipex->path, del);
	if (pipex->cmd)
		free_cmd_tab(pipex);
}
