/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:45:01 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/12 15:30:34 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	split_and_store_args(char **argv)
{
	char	**splitted_args;
	int		i;

	splitted_args = ft_split(argv[1], '|');
	i = -1;
	while (splitted_args[++i])
		argv[i + 1] = splitted_args[i];
}

int	count_words(char *argv)
{
	int	nb_words;

	nb_words = 0;
	while (*argv && argv++)
	{
		if (*argv == ' ' || *argv == '<' || *argv == '>')
		{
			if (ft_strncmp((char *)argv, "<<", 2) == 0
				|| ft_strncmp((char *)argv, ">>", 2) == 0)
				argv++;
			if (*argv == '<' || *argv == '>')
			{
				argv++;
				nb_words--;
			}
			nb_words++;
		}
	}
	return (nb_words + 1);
}

void	split_words(t_pipe *pipex, char *argv, char ***splitted_words)
{
	int		nb_words;
	int		start;
	int		len;
	char	**tmp;

	nb_words = count_words(argv);
	*splitted_words = ft_calloc_pipex(pipex, nb_words + 1, sizeof(char *));
	tmp = *splitted_words;
	start = 0;
	len = 0;
	while (argv[start] && --nb_words >= 0)
	{
		while (argv[start] && (argv[start] == ' '
				|| argv[start] == '>' || argv[start] == '<'))
			start++;
		len = start;
		while (argv[len]
			&& argv[len] != '<' && argv[len] != '>' && argv[len] != ' ')
			len++;
		if (len != start)
			**splitted_words = ft_substr(argv, start, len - start);
		++*splitted_words;
		start = len;
	}
	*splitted_words = tmp;
}
