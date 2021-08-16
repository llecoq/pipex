/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:56:29 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:56:31 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoabase(unsigned long long nb, char *base)
{
	int						nb_len;
	char					*nb_string;

	nb_len = 0;
	nb_len = hexa_len(nb);
	nb_string = (char *)ft_calloc(sizeof(char), (nb_len + 1));
	if (!(nb_string))
		return (0);
	nb_string[nb_len--] = '\0';
	while (nb >= 16)
	{
		nb_string[nb_len] = base[nb % 16];
		nb_len--;
		nb /= 16;
		if (nb_len < 0)
			break ;
	}
	nb_string[nb_len] = base[nb % 16];
	return (nb_string);
}
