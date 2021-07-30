/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:04:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/30 10:18:39 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	create_argv(t_token *token_list, char ***argv)
{
	while (token_list)
	{
		if (token_list->type == IS_CMD)
		{
			(*argv) = ft_split(token_list->word, ' ');
			return ;
		}
		token_list = token_list->next;
	}
}

static void	execute_file(t_list **path_list, char **argv, char **envp)
{
	char	*file;
	
	file = ft_strjoin((*path_list)->content, *argv);
	execve(file, argv, envp);
	free (file);
	(*path_list) = (*path_list)->next;
}

// static void	dup_redirection(t_pipe *pipex, t_cmd *cmd, t_token *token_list)
// {	
// 	(void)pipex;
// 	(void)token_list;

// 	if (cmd->redir.file)
// 		dup2(cmd->pipefd[1], 1);
// 	else if (cmd->redir.out)
// 		dup2(cmd->pipefd[0], 0);
// 	close(cmd->pipefd[0]);
// 	close(cmd->pipefd[1]);
// }

static void	execution_child_process(t_pipe *pipex, t_cmd *cmd, char **envp)
{
	char	**argv;
	t_list	*path_list;

	// close_unused_fds(cmd, cmd->token_list);
	create_redirection(pipex, cmd, cmd->token_list);
	dup_redirection(pipex, cmd, cmd->token_list);
	create_argv(cmd->token_list, &argv);
	path_list = pipex->path;
	if (path_list == NULL)
	{
		errno = ENOENT;
		error_quit(pipex, *argv, 0);
	}
	while (path_list)
		execute_file(&path_list, argv, envp);
	close(cmd->pipefd[1]);
	close(cmd->pipefd[0]);
	error_quit(pipex, *argv, CMD_NOT_FOUND);
}

void	evaluator(t_pipe *pipex, t_cmd *cmd, char **envp, int nb_of_cmds)
{
	int		i;
	int		status;
	pid_t	pid[nb_of_cmds];

	i = -1;
	while (++i < nb_of_cmds)
	{
		pid[i] = fork();
		cmd->token_list = pipex->token[i];
		if (pid[i] == -1)
			error_quit(pipex, NULL, 0);
		else if (pid[i] == CHILD_PROCESS)
			execution_child_process(pipex, cmd, envp);
		else if (pid[i] >= PARENT_PROCESS)
		{
			close(cmd->pipefd[1]);
			close(cmd->pipefd[0]);
		}
		cmd = cmd->next;
	}
	waitpid(pid[i], &status, 0); // bash ne retourne que la derniere erreur
}
