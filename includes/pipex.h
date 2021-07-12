/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:16:16 by user42            #+#    #+#             */
/*   Updated: 2021/07/10 15:16:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "../libft/libft.h"

enum token
{
	IS_CMD = 1,
	IS_FILE = 2,
	PIPE = 3,
	APPEND = 4,
	HEREDOC = 5,
	STOP_VALUE = 6,
	INPUT_REDIR = 7,
	OUTPUT_REDIR = 8,
};

enum parse
{
	MANDATORY = 1,
	BONUS = 2,
};

typedef struct	s_pipe
{
	t_list			*path;
	struct s_token	**cmd;
}				t_pipe;

typedef struct	s_token
{
	char			*word;
	char			*stop_value;
	int				type;
	int				redir;
	struct s_token	*next;
}				t_token;

/* PARSING */
void	parse(t_pipe *pipex, char **argv, int argc);
void	store_path(t_pipe *pipex);

/* UTILS */
void	clear_memory(t_pipe *pipex);
void	del(void *content);
void	print_list(t_list *list);
void	print_token_list(t_token *list);
void	print_cmd_tab(t_token **cmd_tab);
void	error_quit(t_pipe *pipex, int errnum);
void	*ft_calloc_pipex(t_pipe *pipex, size_t count, size_t size);

/* TOKENIZER */

void	tokenizer(t_pipe *pipex, char **argv, int parse);
void	addback_cmd(t_token **list, t_token *new);
t_token	*new_token(char **content, int type, int redir);

#endif
















