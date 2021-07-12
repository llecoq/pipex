/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:40:27 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 12:06:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	store_path(t_pipe *pipex)
{
	char	**path;
	char	*full_path;
	int		i;

	path = ft_split(getenv("PATH"), ':');
	i = -1;
	while (path[++i])
	{
		full_path = ft_strjoin(path[i], "/");
		ft_lstadd_back(&pipex->path, ft_lstnew(full_path));
	}
	free_split(path);
}
