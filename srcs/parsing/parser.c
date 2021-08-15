/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:19 by user42            #+#    #+#             */
/*   Updated: 2021/08/15 17:18:45 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	init_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->redir.from_heredoc = NONEXISTENT;
		cmd->redir.into_file = NONEXISTENT;
		cmd->redir.into_stdin = NONEXISTENT;
		cmd->redir.from_file = NONEXISTENT;
		cmd = cmd->next;
	}
}

void	parse(t_pipe *pipex, char **argv, int argc)
{
	int	parse;

	parse = MANDATORY;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		parse = BONUS;
	if (parse == BONUS && argc <= 5)
		error_quit(pipex, "not enough arguments\nusage : ./pipex here_doc \
LIMITER cmd cmd1 file", -1);
	store_path(pipex);
	tokenizer(pipex, argv, parse);
	create_empty_cmds_list(pipex, pipex->cmds_nb);
	init_cmd(pipex->cmds);
	if (parse == BONUS)
		create_heredoc(pipex, pipex->cmds, pipex->token[0]->word);
}
