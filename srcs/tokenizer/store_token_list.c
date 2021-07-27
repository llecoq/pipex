/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:42:31 by user42            #+#    #+#             */
/*   Updated: 2021/07/27 11:20:33 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

t_token	*last_token(t_token *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

t_token	*new_token(char **content, int type, int redir)
{
	t_token	*new_elem;

	new_elem = malloc(sizeof(t_token));
	if (!new_elem)
		return (NULL);
	new_elem->type = type;
	new_elem->word = ft_strdup(*content);
	new_elem->redir = redir;
	new_elem->next = NULL;
	new_elem->previous = NULL;
	return (new_elem);
}

void	addback_token(t_token **list, t_token *new)
{
	t_token	*previous;

	if (*list)
	{
		previous = last_token(*list);
		(*list)->next = new;
	}
	else
		*list = new;
}
