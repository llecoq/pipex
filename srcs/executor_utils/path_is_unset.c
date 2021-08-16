/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_is_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:57:19 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 11:35:57 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	path_is_not_absolute(char **argv, t_list **path_list)
{
	if (*argv[0] == '/' || ft_strncmp("./", *argv, 2) == 0)
	{
		ft_lstadd_back(path_list, ft_lstnew(NULL));
		return (0);
	}
	return (1);
}

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
