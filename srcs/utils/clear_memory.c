/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:02:57 by user42            #+#    #+#             */
/*   Updated: 2021/07/28 11:09:07 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	free_cmd_list(t_cmd **lst)
{
	t_cmd		*tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free_split((*lst)->argv);
		free((*lst));
		(*lst) = NULL;
		*lst = tmp;
	}
	*lst = NULL;	
}

void	free_token_list(t_token **lst)
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

void	free_token_tab(t_pipe *pipex)
{
	int	i;

	i = -1;
	while (pipex->token[++i])
	{
		free_token_list(&pipex->token[i]);
		free(pipex->token[i]);
		pipex->token[i] = NULL;
	}
	free(pipex->token);
	pipex->token = NULL;
}

void	clear_memory(t_pipe *pipex)
{
	if (pipex->path)
		ft_lstclear(&pipex->path, del);
	if (pipex->token)
		free_token_tab(pipex);
	// if (pipex->cmds)
	// 	free_cmd_list(&pipex->cmds);
}
