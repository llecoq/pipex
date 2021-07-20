/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:19 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 12:22:00 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

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
	create_pipe(pipex, pipex->cmds);
	// print_cmds_list(pipex->cmds);
	// build_commands(pipex);
}
