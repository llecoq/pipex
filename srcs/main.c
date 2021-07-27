/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2021/07/27 15:56:27 by llecoq           ###   ########.fr       */
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

int main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	
	(void)envp;
	if ((argc < 5 && argc > 2) || argc < 2)
		error_quit(&pipex, "not enough arguments\nusage :  ./pipex \
file1 cmd1 cmd2 cmd3 ... cmdn file2", -1);
	init_pipex(&pipex);
	parse(&pipex, argv, argc);
	evaluator(&pipex, pipex.cmds, envp, pipex.cmds_nb);
	clear_memory(&pipex);
	return (0);
}
