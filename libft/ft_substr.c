/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:58:43 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:58:44 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new;
	size_t		i;
	size_t		s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	if (len > s_len)
		len = s_len;
	new = (char *)malloc(len + 1);
	if (!(new))
		return (0);
	i = -1;
	while (++i < len)
		new[i] = s[start + i];
	new[i] = '\0';
	return (new);
}
