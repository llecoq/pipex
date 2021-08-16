/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:58:35 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:58:37 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			length;

	length = 0;
	while (s[length])
		length++;
	while (length >= 0)
	{
		if (s[length] == c)
			return ((char *)s + length);
		length--;
	}
	return (0);
}
