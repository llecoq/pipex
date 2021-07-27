/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:42:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/27 16:50:50 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

t_cmd	*last_cmd(t_cmd *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

t_cmd	*new_cmd(t_pipe *pipex)
{
	t_cmd	*new_elem;

	new_elem = malloc(sizeof(t_cmd));
	if (!new_elem)
		error_quit(pipex, NULL, 0);
	new_elem->token_list = NULL;
	new_elem->argv = NULL;
	new_elem->next = NULL;
	new_elem->previous = NULL;
	return (new_elem);
}

void	addback_cmd(t_cmd **list, t_cmd *new)
{
	t_cmd	*last_elem;

	last_elem = NULL;
	if (*list)
	{
		last_elem = last_cmd(*list);
		last_elem->next = new;
		new->previous = last_elem;
	}
	else
		*list = new;
}

void	create_empty_cmds_list(t_pipe *pipex, int nb_of_cmds)
{
	int	i;

	i = 0;
	while (i < nb_of_cmds)
	{
		addback_cmd(&pipex->cmds, new_cmd(pipex));
		i++;
	}
}
