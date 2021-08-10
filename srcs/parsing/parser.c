/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:19 by user42            #+#    #+#             */
/*   Updated: 2021/08/10 19:37:31 by llecoq           ###   ########.fr       */
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
		cmd->redir.from_heredoc = NONEXISTENT;
		cmd->redir.into_file = NONEXISTENT;
		cmd->redir.into_stdin = NONEXISTENT;
		cmd->redir.from_file = NULL;
		cmd = cmd->next;
	}
}

void	prompt(t_pipe *pipex, char *stop_value, int fd)
{
	char	*input;
	
	(void)pipex;
	(void)fd;
	write(STDOUT_FILENO, "> ", 2);
	while (get_next_line(STDIN_FILENO, &input) > 0)
	{
		if (strncmp(input, stop_value, ft_strlen(stop_value) + 1) == 0)
			return ;
		write(STDOUT_FILENO, "> ", 2);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
}

// bash creer un tmp file mais pipe plus propre je pense
void	create_heredoc(t_pipe *pipex, t_cmd *cmd, char *stop_value)
{
	int		pipefd[2];

	if (pipe(pipefd) == FAILED)
		error_quit(pipex, NULL, 0);
	cmd->redir.from_heredoc = pipefd[1];
	prompt(pipex, stop_value, cmd->redir.from_heredoc);
	cmd->redir.from_heredoc = pipefd[0];
	close(pipefd[1]);
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
	create_empty_cmds_list(pipex, pipex->cmds_nb);
	create_pipes(pipex, pipex->cmds);
	if (parse == BONUS)
		create_heredoc(pipex, pipex->cmds, pipex->token[0]->word);
	
	pipex->fd = open("file", O_CREAT | O_RDWR | O_APPEND, 0644);
}
