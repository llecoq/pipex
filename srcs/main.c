/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2021/08/14 20:26:13 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipe *pipex)
{
	pipex->path = NULL;
	pipex->token = NULL;
	pipex->cmds = NULL;
	pipex->cmds_nb = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	int		child_status;

	if ((argc < 5 && argc > 2) || argc < 2)
		error_quit(&pipex, "not enough arguments\nusage :  ./pipex \
file1 cmd1 cmd2 cmd3 ... cmdn file2", -1);
	init_pipex(&pipex);
	parse(&pipex, argv, argc);
	child_status = evaluator(&pipex, pipex.cmds, envp, pipex.cmds_nb);
	clear_memory(&pipex);
	return (child_status);
}
