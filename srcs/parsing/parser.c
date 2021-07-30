/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:19 by user42            #+#    #+#             */
/*   Updated: 2021/07/30 10:19:34 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	create_pipe(t_pipe *pipex, t_cmd *cmds)
{
	while (cmds)
	{
		if (pipe(cmds->pipefd) == -1)
			error_quit(pipex, NULL, 0);
		cmds->redir.into_file = 0;
		cmds->redir.into_stdin = 0;
		cmds->redir.from_file = 0;
		cmds = cmds->next;
	}
}

void	parse(t_pipe *pipex, char **argv, int argc)
{
	int	parse;

	parse = MANDATORY;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		parse = BONUS;
	if (parse == BONUS && argc == 5)
		error_quit(pipex, "not enough arguments\nusage : ./pipex here_doc \
LIMITER cmd cmd1 file", -1);
	store_path(pipex);
	tokenizer(pipex, argv, parse);
// CHECK SI HEREDOC, A CREER AVANT L'EXECUTOR
	create_empty_cmds_list(pipex, pipex->cmds_nb);
	create_pipe(pipex, pipex->cmds);

	// print_cmds_list(pipex->cmds);
}
