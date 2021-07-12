/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:46:07 by user42            #+#    #+#             */
/*   Updated: 2021/07/09 09:05:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	error_quit(t_pipe *pipex, int errnum)
{
	if (errnum == 0)
	{
	//	write(2, (char *)perror(errno), ft_strlen((char *)perror(errno)));
		dprintf(1, "OOOH\n");
	}
	clear_memory(pipex);
	exit(EXIT_FAILURE);
}
