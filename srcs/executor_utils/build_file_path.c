/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_file_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:39:14 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/15 16:40:57 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	argument_is_a_script(char **argv, char **tmp, char **file)
{
	if (ft_strncmp(argv[0], "./", 2) == 0)
	{
		*file = "/bin/sh";
		*tmp = ft_strjoin("sh ", argv[0]);
		free_split(argv);
		return (1);
	}
	return (0);
}

static int	argument_is_a_path(char **file, char **argv)
{
	if (*argv[0] == '/')
	{
		(*file) = (*argv);
		return (1);
	}
	return (0);
}

void	build_file_path(t_list **path_list, t_file *file, char **argv)
{
	file->file = NULL;
	file->tmp = NULL;
	file->arg_type = 0;
	if (argument_is_a_path(&file->file, argv))
		file->arg_type = IS_PATH;
	else if (argument_is_a_script(argv, &file->tmp, &file->file))
		argv = ft_split(file->tmp, ' ');
	else
		file->file = ft_strjoin((*path_list)->content, *argv);
}
