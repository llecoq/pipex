/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:10:43 by user42            #+#    #+#             */
/*   Updated: 2021/08/14 20:36:38 by llecoq           ###   ########.fr       */
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

void	print_token_tab(t_token **token_tab)
{
	int	i;

	i = -1;
	while (token_tab[++i])
	{
		ft_putstr_fd("-------------\n", 1);
		print_token_list(token_tab[i]);
	}
}

void	print_str_tab(char **str_tab)
{
	int	i;

	i = -1;
	write(1, "--------------------\n", 22);
	while (str_tab[++i])
	{
		ft_putstr_fd(str_tab[i], 1);
		write(1, "\n", 1);
	}
}

void	print_cmds_list(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->argv)
			print_str_tab(cmds->argv);
		cmds = cmds->next;
	}
}
