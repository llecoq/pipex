/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:19 by user42            #+#    #+#             */
/*   Updated: 2021/07/21 12:06:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	count_valid_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds)
	{
		if (cmds->args)
			i++;
		cmds = cmds->next;
	}
	return (i);
}

void	create_pipe(t_pipe *pipex, t_cmd *cmds)
{
	(void)pipex;
	while (cmds)
	{
		pipe(cmds->pipefd);
		cmds = cmds->next;
	}
}

void	parse(t_pipe *pipex, char **argv, int argc)
{
	int	parse;

	parse = MANDATORY;
	if (argc == 2)
		parse = BONUS;
	store_path(pipex);
	tokenizer(pipex, argv, parse);
	// print_token_tab(pipex->token);
	set_redirection(pipex, &pipex->token);
	store_cmds(pipex, pipex->token);
	pipex->cmds_nb = count_valid_cmds(pipex->cmds);
	create_pipe(pipex, pipex->cmds);
	dprintf(1, "nb_of_cmds = %d\n", pipex->cmds_nb);
//	print_token_tab(pipex->token);
//	print_cmds_list(pipex->cmds);
	// build_commands(pipex);
}
