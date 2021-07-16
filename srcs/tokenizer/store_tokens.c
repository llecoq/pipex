/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:38:11 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/16 12:49:39 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	find_type_of_redirection(char *splitted_word, char *argv, int type)
{
	int		redir;
	char	*word;

	redir = 0;
	word = ft_strnstr(argv, splitted_word, ft_strlen(splitted_word));
	if (type == IS_CMD)
	{
		if (ft_strchr(word, '|'))
			type = PIPE;

	}
	return (redir);
}

void	store_words(t_pipe *pipex, char **splitted_words, char *argv, int i)
{
	int	type;
	int	redir;

	(void)argv;
	type = 0;
	while (*splitted_words && ++type)
	{
		redir = find_type_of_redirection(*splitted_words, argv, type);
		addback_token(&pipex->token[i], new_token(splitted_words, type, redir));
		++splitted_words; 
	}
}

void	store_bonus_tokens(t_pipe *pipex, char **argv)
{
	char	**splitted_args;
	char	**splitted_words;
	int		i;

	splitted_args = ft_split(argv[1], '|');
	i = -1;
	while (splitted_args[++i])
	{
		splitted_words = NULL;
		split_words(pipex, splitted_args[i], &splitted_words);
		store_words(pipex, splitted_words, argv[1], i);
		free_split(splitted_words);
	}
	free_split(splitted_args);
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
	addback_token(&pipex->token[cmd_nb], new_token(++argv, IS_CMD, PIPE));
	addback_token(&pipex->token[cmd_nb], new_token(++argv, IS_FILE, OUTPUT_REDIR));
}
