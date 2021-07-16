/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 11:00:17 by user42            #+#    #+#             */
/*   Updated: 2021/07/16 11:33:21 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	*ft_calloc_pipex(t_pipe *pipex, size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			nb_bytes;

	ptr = malloc(count * size);
	if (!(ptr))
		error_quit(pipex, NULL, 0);
	nb_bytes = count * size;
	while (nb_bytes)
	{
		ptr[nb_bytes - 1] = 0;
		nb_bytes--;
	}
	return (ptr);
}
