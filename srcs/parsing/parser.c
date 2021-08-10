/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:19 by user42            #+#    #+#             */
/*   Updated: 2021/08/10 12:02:14 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	close_all_pipes(t_cmd *cmd)
{
	t_cmd	*previous_cmd;

	previous_cmd = cmd->previous;
	while (previous_cmd)
	{
		close(previous_cmd->pipefd[0]);
		close(previous_cmd->pipefd[1]);
		previous_cmd = previous_cmd->previous;
	}
}

void	create_pipes(t_pipe *pipex, t_cmd *cmd)
{
	while (cmd)
	{
		if (pipe(cmd->pipefd) == FAILED)
		{
			close_all_pipes(cmd);
			error_quit(pipex, NULL, 0);
		}
		cmd->redir.into_file = NONEXISTENT;
		cmd->redir.into_stdin = NONEXISTENT;
		cmd->redir.from_file = NULL;
		cmd = cmd->next;
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
	create_pipes(pipex, pipex->cmds);
	// print_cmds_list(pipex->cmds);
}
