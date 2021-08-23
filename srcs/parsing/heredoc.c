/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 10:40:21 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/23 09:23:50 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	write_into_fd(int fd, char *input)
{
	write(STDOUT_FILENO, "> ", 2);
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
}

static void	prompt(t_pipe *pipex, char *stop_value, int fd)
{
	char	*input;
	int		ret;

	input = NULL;
	ret = 1;
	write(STDOUT_FILENO, "> ", 2);
	while (ret > 0)
	{
		ret = get_next_line(STDIN_FILENO, &input);
		if (ret == -1)
			error_quit(pipex, NULL, 0);
		if (ft_strncmp(input, stop_value, ft_strlen(stop_value) + 1) == 0)
			return ;
		if (*input)
			write_into_fd(fd, input);
		else
			write(STDOUT_FILENO, "\n", 1);
		if (input)
			free_set_null(&input);
	}
	if (input)
		free_set_null(&input);
}

void	create_heredoc(t_pipe *pipex, t_cmd *cmd, char *stop_value)
{
	int		pipefd[2];

	if (pipe(pipefd) == FAILED)
		error_quit(pipex, NULL, SYSCALL_ERROR);
	prompt(pipex, stop_value, pipefd[1]);
	close(pipefd[1]);
	cmd->redir.from_heredoc = pipefd[0];
}
