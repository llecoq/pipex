/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:58:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:58:10 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int			s1_len;
	int			s2_len;
	char		*r;
	int			i;
	int			j;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	r = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!(r))
		return (0);
	i = -1;
	while (++i < s1_len)
		r[i] = s1[i];
	j = -1;
	while (++j < s2_len)
		r[i + j] = s2[j];
	r[i + j] = '\0';
	return (r);
}
