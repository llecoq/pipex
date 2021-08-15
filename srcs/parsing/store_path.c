/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:40:27 by user42            #+#    #+#             */
/*   Updated: 2021/08/15 15:09:57 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_env(t_pipe *pipex, const char *name)
{
	size_t	len;
	size_t	i;
	char	*var_value;

	var_value = NULL;
	len = ft_strlen(name);
	i = 0;
	while (pipex->envp[i])
	{
		if (ft_strncmp(pipex->envp[i], name, len) == 0
			&& pipex->envp[i][len] == '=')
		{
			var_value = ft_strchr(pipex->envp[i], '=') + 1;
			while (*var_value == ' ')
				var_value++;
			return (var_value);
		}
		i++;
	}
	return (NULL);
}

void	store_path(t_pipe *pipex)
{
	char	**path_tab;
	char	*path;
	char	*full_path;
	int		i;

	path = get_env(pipex, "PATH");
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
