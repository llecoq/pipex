/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:58:04 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:58:06 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		s_len;
	char	*s_bis;
	int		i;

	s_len = ft_strlen(s1);
	s_bis = NULL;
	if (!(ft_malloc(s_bis, sizeof(char) * (s_len + 1))))
		return (0);
	i = -1;
	while (s1[++i])
		s_bis[i] = s1[i];
	s_bis[i] = '\0';
	return (s_bis);
}
