/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:57:02 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 09:57:03 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list			*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (!(res))
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}
