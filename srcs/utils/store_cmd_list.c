/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 14:42:31 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 17:14:43 by user42           ###   ########.fr       */
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
	new_elem->stop_value = NULL;
	new_elem->redir = redir;
	new_elem->next = NULL;
	return (new_elem);
}

void	addback_cmd(t_token **list, t_token *new)
{
	if (*list)
		last_token(*list)->next = new;
	else
		*list = new;
}
