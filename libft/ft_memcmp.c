/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:57:22 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:57:23 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*s1bis;
	const unsigned char		*s2bis;
	unsigned int			i;

	if (n == 0)
		return (0);
	i = 0;
	s1bis = s1;
	s2bis = s2;
	while (i < n)
	{
		if (s1bis[i] != s2bis[i])
			return (s1bis[i] - s2bis[i]);
		i++;
	}
	return (s1bis[i - 1] - s2bis[i - 1]);
}
