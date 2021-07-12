/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:10:43 by user42            #+#    #+#             */
/*   Updated: 2021/07/10 14:44:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	print_list(t_list *list)
{
	while (list)
	{
		write(1, (char *)list->content, ft_strlen((char *)list->content));
		write(1, "\n", 1);
		list = list->next;
	}
}

void	print_token_list(t_token *list)
{
	while (list)
	{
		write(1, (char *)list->word, ft_strlen((char *)list->word));
		write(1, "\n", 1);
		list = list->next;
	}
}

void	print_cmd_tab(t_token **cmd_tab)
{
	int	i;

	i = -1;
	while (cmd_tab[++i])
	{
		ft_putstr_fd("-------------\n", 1);
		print_token_list(cmd_tab[i]);
	}
}
