/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 10:16:16 by user42            #+#    #+#             */
/*   Updated: 2021/08/15 16:49:21 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/gnl/get_next_line.h"
# include "enum.h"

typedef struct s_pipe
{
	t_list			*path;
	struct s_token	**token;
	struct s_cmd	*cmds;
	char			**envp;
	int				cmds_nb;
}				t_pipe;

typedef struct s_cmd
{
	char			**argv;
	int				pipefd[2];
	struct s_redir	redir;
	struct s_token	*token_list;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_redir
{
	int				into_file;
	int				into_stdin;
	int				from_heredoc;
	int				from_file;
}				t_redir;

typedef struct s_token
{
	char			*word;
	int				type;
	int				redir;
	struct s_token	*next;
	struct s_token	*previous;
}				t_token;

typedef struct s_file
{
	char			*file;
	char			*tmp;
	char			**argv;
	int				arg_type;
}				t_file;

/* PARSING */
void	parse(t_pipe *pipex, char **argv, int argc);
void	store_path(t_pipe *pipex);
void	split_words(t_pipe *pipex, char *argv, char ***splitted_words);
void	split_and_store_args(char **argv);
void	create_empty_cmds_list(t_pipe *pipex, int nb_of_cmds);
void	create_heredoc(t_pipe *pipex, t_cmd *cmd, char *stop_value);

/* TOKENIZER */
void	store_mandatory_tokens(t_pipe *pipex, char **argv, int cmd_nb);
void	store_bonus_tokens(t_pipe *pipex, char **argv, int cmd_nb);
void	tokenizer(t_pipe *pipex, char **argv, int parse);
void	addback_token(t_token **list, t_token *new);
t_token	*new_token(char **content, int type, int redir);

/* EXECUTOR */
int		evaluator(t_pipe *pipex, t_cmd *cmds, int nb_of_cmds);
void	create_redirection(t_pipe *pipex, t_cmd *cmd, t_token *token_list);
void	dup_input_redirection(t_pipe *pipex, t_cmd *cmd);
void	dup_output_redirection(t_pipe *pipex, t_cmd *cmd);

/* EXECUTOR UTILS*/
int		last_child_status(pid_t last_child_pid);
int		path_is_unset(t_pipe *pipex, t_list **path_list);
int		path_is_not_absolute(char **argv, t_list **path_list);
int		create_argv(t_token *token_list, char ***split_argv);
void	create_pipe(t_pipe *pipex, t_cmd *cmd);
void	build_file_path(t_list **path_list, t_file *file, char **argv);

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

#endif
