/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:46:07 by user42            #+#    #+#             */
/*   Updated: 2021/07/27 16:56:26 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

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
	char	*error_msg;
	
	(void)pipex;
	error_msg = strerror(errno);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	if (errnum != -1)
		ft_putstr_fd(": ", 2);	
	if (errnum == 0)
		ft_putstr_fd(error_msg, 2);
	if (errnum == 1)
		ft_putstr_fd("command not found", 2);
	ft_putchar_fd('\n', 2);
	clear_memory(pipex);
	exit(errno);
}
