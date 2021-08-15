/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:20:37 by user42            #+#    #+#             */
/*   Updated: 2021/08/15 17:41:17 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	count_number_of_commands(char **argv, int parse)
{
	int	nb_of_cmds;

	nb_of_cmds = -1;
	while (argv[nb_of_cmds])
		nb_of_cmds++;
	if (parse == MANDATORY)
		nb_of_cmds -= 3;
	else if (parse == BONUS)
		nb_of_cmds -= 4;
	return (nb_of_cmds);
}

void	tokenizer(t_pipe *pipex, char **argv, int parse)
{
	int	nb_of_cmd;

	nb_of_cmd = 0;
	if (parse == MANDATORY)
		nb_of_cmd = count_number_of_commands(argv, MANDATORY);
	else if (parse == BONUS)
		nb_of_cmd = count_number_of_commands(argv, BONUS);
	pipex->cmds_nb = nb_of_cmd;
	pipex->token = ft_calloc_pipex(pipex, nb_of_cmd + 1, sizeof(t_token *));
	if (parse == MANDATORY)
		store_mandatory_tokens(pipex, argv, nb_of_cmd);
	else if (parse == BONUS)
		store_bonus_tokens(pipex, argv, nb_of_cmd);
}
