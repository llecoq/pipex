/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:38:11 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/18 15:28:53 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	store_bonus_tokens(t_pipe *pipex, char **argv, int cmd_nb)
{
	int	i;

	argv++;
	addback_token(&pipex->token[0], new_token(++argv, HEREDOC, STOP_VALUE));
	addback_token(&pipex->token[0], new_token(++argv, IS_CMD, PIPE));
	cmd_nb--;
	i = 0;
	while (++i < cmd_nb)
		addback_token(&pipex->token[i], new_token(++argv, IS_CMD, PIPE));
	addback_token(&pipex->token[cmd_nb], new_token(++argv, IS_CMD, APPEND));
	addback_token(&pipex->token[cmd_nb], new_token(++argv, IS_FILE, APPEND));
}

void	store_mandatory_tokens(t_pipe *pipex, char **argv, int cmd_nb)
{
	int	i;

	addback_token(&pipex->token[0], new_token(++argv, IS_FILE, INPUT_REDIR));
	addback_token(&pipex->token[0], new_token(++argv, IS_CMD, PIPE));
	cmd_nb--;
	i = 0;
	while (++i < cmd_nb)
		addback_token(&pipex->token[i], new_token(++argv, IS_CMD, PIPE));
	addback_token(&pipex->token[cmd_nb], new_token(++argv, IS_CMD, \
	TRUNC));
	addback_token(&pipex->token[cmd_nb], new_token(++argv, IS_FILE, \
	TRUNC));
}
