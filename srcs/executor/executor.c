/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:04:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/16 14:01:36 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	execute_file(t_pipe *pipex, t_list **path_list, char ***argv)
{
	char	**envp;
	t_file	file;

	envp = pipex->envp;
	build_file_path(path_list, &file, argv);
	execve(file.file, (*argv), envp);
	if (file.arg_type == IS_PATH)
	{
		errno = ENOENT;
		error_quit(pipex, (**argv), 0);
	}
	free_set_null(&file.tmp);
	free_set_null(&file.file);
	(*path_list) = (*path_list)->next;
}

static void	execution_child_process(t_pipe *pipex, t_cmd *cmd)
{
	char	**argv;
	t_list	*path_list;

	create_redirection(pipex, cmd, cmd->token_list);
	dup_input_redirection(pipex, cmd);
	dup_output_redirection(pipex, cmd);
	if (create_argv(cmd, cmd->token_list, &argv) == FAILED)
		error_quit(pipex, NULL, 0);
	if (path_is_unset(pipex, &path_list)
		&& path_is_not_absolute(argv, &path_list))
		error_quit(pipex, *argv, 0);
	while (path_list != NULL)
		execute_file(pipex, &path_list, &argv);
	error_quit(pipex, *argv, CMD_NOT_FOUND);
}

void	close_fds(t_cmd *cmd)
{
	close(cmd->pipefd[1]);
	if (cmd->previous)
		close(cmd->previous->pipefd[0]);
	if (!cmd->next)
		close(cmd->pipefd[0]);
}

int	evaluator(t_pipe *pipex, t_cmd *cmd, int nb_of_cmds)
{
	int		i;
	pid_t	pid[2048];

	i = -1;
	while (++i < nb_of_cmds)
	{
		create_pipe(pipex, cmd);
		pid[i] = fork();
		cmd->token_list = pipex->token[i];
		if (pid[i] == FAILED)
			error_quit(pipex, NULL, 0);
		else if (pid[i] == CHILD_PROCESS)
			execution_child_process(pipex, cmd);
		else if (pid[i] >= PARENT_PROCESS)
			close_fds(cmd);
		cmd = cmd->next;
	}
	return (last_child_status(pid[i - 1]));
}
