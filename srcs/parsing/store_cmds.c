/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:42:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/18 12:18:36 by llecoq           ###   ########.fr       */
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

t_cmd	*new_cmd(char **content)
{
	t_cmd	*new_elem;

	new_elem = malloc(sizeof(t_cmd));
	if (!new_elem)
		return (NULL);
	new_elem->args = content;
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

void	store_cmds(t_pipe *pipex, t_token **token_list)
{
	t_token	*head;
	char	**splitted_token;
	int		i;

	i = -1;
	while (token_list[++i])
	{
		head = token_list[i];
		while (token_list[i])
		{
			if (token_list[i]->type == IS_CMD
				&& head->cmd == IS_VALID)
			{
				splitted_token = ft_split(token_list[i]->word, ' ');
				addback_cmd(&pipex->cmds, new_cmd(splitted_token));
			}
			else if (token_list[i]->type == IS_CMD
				&& head->cmd == IS_NOT_VALID)
				addback_cmd(&pipex->cmds, new_cmd(NULL));
			token_list[i] = token_list[i]->next;
		}
		token_list[i] = head;
	}
}
