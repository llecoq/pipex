/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:55:47 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:55:49 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char		*ptr;
	size_t				nb_bytes;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	nb_bytes = count * size;
	while (nb_bytes)
	{
		ptr[nb_bytes - 1] = 0;
		nb_bytes--;
	}
	return (ptr);
}
