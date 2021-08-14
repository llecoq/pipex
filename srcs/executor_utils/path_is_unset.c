/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_is_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:57:19 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/14 17:58:09 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	path_is_unset(t_pipe *pipex, t_list **path_list)
{
	(*path_list) = pipex->path;
	
	if ((*path_list) == NULL)
	{
		errno = ENOENT;
		return (1);
	}
	return (0);
}
