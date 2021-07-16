/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:20:37 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 19:04:09 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	count_bonus_cmds(char **argv)
{
	int	nb_of_cmds;
	int	i;

	nb_of_cmds = 1;
	i = -1;
	while (argv[1][++i])
		if (argv[1][i] == '|')
			nb_of_cmds++;
	return (nb_of_cmds);
}

int	count_number_of_commands(char **argv, int parse)
{
	int	nb_of_cmds;

	nb_of_cmds = -1;
	if (parse == MANDATORY)
	{
		while (argv[nb_of_cmds])
			nb_of_cmds++;
		return (nb_of_cmds - 3);
	}
	else if (parse == BONUS)
		nb_of_cmds = count_bonus_cmds(argv);
	return (nb_of_cmds);
}

void	tokenizer(t_pipe *pipex, char **argv, int parse)
{
	int	cmd_nb;

	cmd_nb = 0;
	if (parse == MANDATORY)
		cmd_nb = count_number_of_commands(argv, MANDATORY);
	else if (parse == BONUS)
		cmd_nb = count_number_of_commands(argv, BONUS);
	pipex->token = ft_calloc_pipex(pipex, cmd_nb + 1, sizeof(t_token *));
	if (parse == MANDATORY)
		store_mandatory_tokens(pipex, argv, cmd_nb);
	else if (parse == BONUS)
		store_bonus_tokens(pipex, argv);

	// print_cmd_tab(pipex->token);
}
