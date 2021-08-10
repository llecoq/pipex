/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:04:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/10 13:40:26 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	join_argv_with_file_name(char **unsplit_argv, char *file_name)
{
	char	*tmp;

	tmp = ft_strjoin(*unsplit_argv, " ");
	free(*unsplit_argv);
	*unsplit_argv = ft_strjoin(tmp, file_name);
	free(tmp);
}

int	create_argv(t_token *token_list, char ***split_argv, char *file_name)
{
	char	*unsplit_argv;

	while (token_list)
	{
		if (token_list->type == IS_CMD)
		{
			unsplit_argv = ft_strdup(token_list->word);
			if (file_name)
				join_argv_with_file_name(&unsplit_argv, file_name);
			(*split_argv) = ft_split(unsplit_argv, ' ');
			free(unsplit_argv);
			return (0);
		}
		token_list = token_list->next;
	}
	return (FAILED);
}

static void	execute_file(t_list **path_list, char **argv, char **envp)
{
	char	*file;
	
	file = ft_strjoin((*path_list)->content, *argv);
	execve(file, argv, envp);
	free (file);
	(*path_list) = (*path_list)->next;
}

static void	close_fds_and_exit(t_pipe *pipex, int fd_1, int fd_2)
{
	if (fd_1 >= EXISTENT)
		close(fd_1);
	if (fd_2 >= EXISTENT)
		close(fd_2);
	error_quit(pipex, NULL, 0);
}

// // proteger dup +  gerer sortie erreur 2 + close fd
void	dup_output_redirection(t_pipe *pipex, t_cmd *cmd)
{
	if (cmd->redir.into_stdin == EXISTENT)
	{
		close(cmd->next->pipefd[0]);
		if (dup2(cmd->next->pipefd[1], STDOUT_FILENO) == FAILED)
			close_fds_and_exit(pipex, cmd->pipefd[1], cmd->next->pipefd[1]);
		close(cmd->next->pipefd[1]);
	}
	else if (cmd->redir.into_file >= EXISTENT)
		if (dup2(cmd->redir.into_file, STDOUT_FILENO) == FAILED)
			close_fds_and_exit(pipex, cmd->pipefd[1], -1);
	close(cmd->pipefd[1]);
}

void	dup_input_redirection(t_pipe *pipex, t_cmd *cmd)
{
	if (dup2(cmd->pipefd[0], STDIN_FILENO) == FAILED)
	{
		close(cmd->pipefd[0]);
		close(cmd->pipefd[1]);
		if (cmd->next)
		{
			close(cmd->next->pipefd[0]);
			close(cmd->next->pipefd[1]);
		}
		error_quit(pipex, NULL, 0);
	}
	close(cmd->pipefd[0]);
}

static int	path_is_unset(t_pipe *pipex, t_list **path_list)
{
	(*path_list) = pipex->path;
	
	if ((*path_list) == NULL)
	{
		errno = ENOENT;
		return (1);
	}
	return (0);
}

void	close_unused_fds(t_cmd *cmd)
{
	t_cmd	*previous_cmd;
	t_cmd	*next_cmd;

	next_cmd = NULL;
	previous_cmd = cmd->previous;
	while (previous_cmd)
	{
		close(previous_cmd->pipefd[0]);
		close(previous_cmd->pipefd[1]);
		previous_cmd = previous_cmd->previous;
	}
	if (cmd->next)
		next_cmd = cmd->next->next;
	while (next_cmd)
	{
		close(next_cmd->pipefd[0]);
		close(next_cmd->pipefd[1]);
		next_cmd = next_cmd->next;
	}
}

static void	execution_child_process(t_pipe *pipex, t_cmd *cmd, char **envp)
{
	char	**argv;
	t_list	*path_list;

	close_unused_fds(cmd);
	create_redirection(pipex, cmd, cmd->token_list);
	dup_input_redirection(pipex, cmd);
	dup_output_redirection(pipex, cmd);
	if (create_argv(cmd->token_list, &argv, cmd->redir.from_file) == FAILED)
		error_quit(pipex, NULL, 0);
	if (path_is_unset(pipex, &path_list))
		error_quit(pipex, *argv, 0);
	while (path_list)
		execute_file(&path_list, argv, envp);
	close(cmd->pipefd[1]);
	close(cmd->pipefd[0]);
	error_quit(pipex, *argv, CMD_NOT_FOUND);
}

int	wexitstatus(int status)
{
	int	w_int;

	w_int = (*(int *)&(status));
	return (((w_int >> 8) & 0x000000ff));
}

int	evaluator(t_pipe *pipex, t_cmd *cmd, char **envp, int nb_of_cmds)
{
	int		i;
	int		child_status;
	pid_t	pid[nb_of_cmds];

	i = -1;
	while (++i < nb_of_cmds)
	{
		pid[i] = fork();
		cmd->token_list = pipex->token[i];
		if (pid[i] == FAILED)
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
	waitpid(pid[i - 1], &child_status, 0); // bash ne retourne que la derniere erreur
	child_status = wexitstatus(child_status);
	return (child_status);
}
