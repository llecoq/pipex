/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:57:18 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:57:20 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_bis;
	unsigned char	c_bis;

	if (n == 0)
		return (0);
	s_bis = (unsigned char *)s;
	c_bis = (unsigned char)c;
	i = 0;
	while (s_bis[i] != c_bis && i < n - 1)
		i++;
	if (s_bis[i] == c_bis)
		return ((void *)(s + i));
	return (0);
}
