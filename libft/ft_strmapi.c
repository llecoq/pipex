/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:58:24 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:58:25 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int			s_len;
	char		*result;
	int			i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	result = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!(result))
		return (NULL);
	i = -1;
	while (++i < s_len)
		result[i] = f(i, s[i]);
	result[i] = '\0';
	return (result);
}
