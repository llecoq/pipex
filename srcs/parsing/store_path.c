/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:40:27 by user42            #+#    #+#             */
/*   Updated: 2021/07/28 12:52:59 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	store_path(t_pipe *pipex)
{
	char	**path_tab;
	char	*path;
	char	*full_path;
	int		i;

	path = getenv("PATH");
	if (path == NULL)
		return ;
	path_tab = ft_split(path, ':');
	i = -1;
	while (path_tab[++i])
	{
		full_path = ft_strjoin(path_tab[i], "/");
		ft_lstadd_back(&pipex->path, ft_lstnew(full_path));
	}
	free_split(path_tab);
}
