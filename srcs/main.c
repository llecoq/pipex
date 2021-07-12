/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:15:32 by user42            #+#    #+#             */
/*   Updated: 2021/07/10 15:14:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(t_pipe *pipex)
{
	pipex->path = NULL;
	pipex->cmd = NULL;
}

int main(int argc, char **argv)
{
	t_pipe	pipex;
	
	if ((argc < 5 && argc > 2) || argc < 2)
		return (0);
	init_pipex(&pipex);
	parse(&pipex, argv, argc);
	// executor(pipex);
	clear_memory(&pipex);
}