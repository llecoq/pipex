/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:46:07 by user42            #+#    #+#             */
/*   Updated: 2021/08/10 13:40:46 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*full_message;

	full_message = ft_strjoin(s1, s2);
	free(s1);
	return (full_message);
}

void	error(t_pipe *pipex, char *str, int errnum)
{
	char	*error_msg;
	
	(void)pipex;
	error_msg = strerror(errno);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);	
	if (errnum == 0)
		ft_putstr_fd(error_msg, 2);
	ft_putchar_fd('\n', 2);
}

void	error_quit(t_pipe *pipex, char *str, int errnum)
{
	char	*errno_msg;
	char	*full_error_msg;

	errno_msg = strerror(errno);
	full_error_msg = join_and_free(ft_strdup("pipex: "), str);
	if (errnum != -1)
		full_error_msg = join_and_free(full_error_msg, ": ");
	if (errnum == 0)
		full_error_msg = join_and_free(full_error_msg, errno_msg);
	if (errnum == CMD_NOT_FOUND)
	{
		errno = CMD_NOT_FOUND;
		full_error_msg = join_and_free(full_error_msg, "command not found");
	}
	full_error_msg = join_and_free(full_error_msg, "\n");
	ft_putstr_fd(full_error_msg, 2);
	clear_memory(pipex);
	exit(errno);
}
