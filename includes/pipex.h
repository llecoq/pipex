/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:16:16 by user42            #+#    #+#             */
/*   Updated: 2021/07/21 11:31:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
	BONUS = 1,
	MANDATORY = 2,
};

enum file
{
	EXISTENT,
	NONEXISTENT,
	IS_VALID = 1,
	IS_NOT_VALID = 0,
};

typedef struct	s_pipe
{
	t_list			*path;
	struct s_token	**token;
	struct s_cmd	*cmds;
	int				cmds_nb;
}				t_pipe;

typedef struct	s_cmd
{
	char			**args;
	int				pipefd[2];
	struct s_cmd	*previous;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_token
{
	char			*word;
	int				type;
	int				redir;
	int				cmd;
	int				fd;
	struct s_token	*next;
}				t_token;

/* PARSING */
void	parse(t_pipe *pipex, char **argv, int argc);
void	store_path(t_pipe *pipex);
void	split_words(t_pipe *pipex, char *argv, char ***splitted_words);
void	split_and_store_args(char **argv);
void	store_cmds(t_pipe *pipex, t_token **token_list);
void	set_redirection(t_pipe *pipex, t_token ***token_tab);
void	create_pipe(t_pipe *pipex, t_cmd *cmds);

/* UTILS */
void	clear_memory(t_pipe *pipex);
void	del(void *content);
void	print_list(t_list *list);
void	print_cmds_list(t_cmd *cmds);
void	print_token_list(t_token *list);
void	print_token_tab(t_token **token_tab);
void	error_quit(t_pipe *pipex, char *str, int errnum);
void	error(t_pipe *pipex, char *str, int errnum);
void	*ft_calloc_pipex(t_pipe *pipex, size_t count, size_t size);

/* TOKENIZER */
void	store_mandatory_tokens(t_pipe *pipex, char **argv, int cmd_nb);
void	store_bonus_tokens(t_pipe *pipex, char **argv);
void	tokenizer(t_pipe *pipex, char **argv, int parse);
void	addback_token(t_token **list, t_token *new);
t_token	*new_token(char **content, int type, int redir);

/* EXECUTOR */
void	executor(t_pipe *pipex);

#endif
















