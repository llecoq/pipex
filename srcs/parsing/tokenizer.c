/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:20:37 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 17:24:52 by user42           ###   ########.fr       */
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

// nul mais marche que lorsque cmds simples sinon SEG ou chiasse
int	count_words(char *argv)
{
	int	nb_words;

	nb_words = 0;
	while (*argv && argv++)
	{
		if (*argv == '|' || *argv == ' ' || *argv == '<' || *argv == '>')
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
	return (nb_words);
}

//leaks
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
		**splitted_words = ft_substr(argv, start, len - start);
		++*splitted_words;
		start = len;
	}
	*splitted_words = tmp;
}

// on a perdu tous les pipes etc; en ammont, essayer d,integrer les redirs dans le split ?
void	store_words(t_pipe *pipex, char **splitted_words, char *argv, int i)
{
	int	type;
	int	redir;

	while (*splitted_words)
	{
		type = find_type_of_word(*splitted_words, argv);
		redir = find_type_of_redirection(*splitted_words, argv);
		addback_cmd(&pipex->cmd[i], new_token(splitted_words, 0, 0));
		++splitted_words; 
	}
	print_token_list(pipex->cmd[i]);
}

void	store_bonus_cmds(t_pipe *pipex, char **argv)
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
		store_words(pipex, splitted_words, splitted_args[i], i);
		free_split(splitted_words);
	}
	free_split(splitted_args);
}

void	store_mandatory_cmds(t_pipe *pipex, char **argv, int cmd_nb)
{
	int	i;

	addback_cmd(&pipex->cmd[0], new_token(++argv, IS_FILE, INPUT_REDIR));
	addback_cmd(&pipex->cmd[0], new_token(++argv, IS_CMD, PIPE));
	cmd_nb--;
	i = 0;
	while (++i < cmd_nb)
		addback_cmd(&pipex->cmd[i], new_token(++argv, IS_CMD, PIPE));
	addback_cmd(&pipex->cmd[cmd_nb], new_token(++argv, IS_CMD, OUTPUT_REDIR));
	addback_cmd(&pipex->cmd[cmd_nb], new_token(++argv, IS_FILE, 0));
}

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

	if (parse == MANDATORY)
	{
		nb_of_cmds = -1;
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

	if (parse == MANDATORY)
		cmd_nb = count_number_of_commands(argv, MANDATORY);
	else if (parse == BONUS)
		cmd_nb = count_number_of_commands(argv, BONUS);
	pipex->cmd = ft_calloc_pipex(pipex, cmd_nb + 1, sizeof(t_token *));
	if (parse == MANDATORY)
		store_mandatory_cmds(pipex, argv, cmd_nb);
	else if (parse == BONUS)
		store_bonus_cmds(pipex, argv);

	print_cmd_tab(pipex->cmd);
}
