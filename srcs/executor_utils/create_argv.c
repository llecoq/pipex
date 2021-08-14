/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 17:59:03 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/14 17:59:19 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	create_argv(t_token *token_list, char ***split_argv)
{
	char	*unsplit_arg;

	while (token_list)
	{
		if (token_list->type == IS_CMD)
		{
			unsplit_arg = token_list->word;
			(*split_argv) = ft_split(unsplit_arg, ' ');
			return (0);
		}
		token_list = token_list->next;
	}
	return (FAILED);
}
