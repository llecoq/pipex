/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:04:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/08/15 12:23:14 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static void	execute_file(t_list **path_list, char **argv, char **envp)
{
	char	*file;
	char	*tmp;

	if (ft_strncmp(argv[0], "./", 2) == 0)
	{
		file = "/bin/sh";
		tmp = ft_strjoin("sh ", argv[0]);
		free_split(argv);
		argv = ft_split(tmp, ' ');
		free(tmp);
	}
	else
		file = ft_strjoin((*path_list)->content, *argv);
	execve(file, argv, envp);
	free (file);
	(*path_list) = (*path_list)->next;
}

static void	execution_child_process(t_pipe *pipex, t_cmd *cmd, char **envp)
{
	char	**argv;
	t_list	*path_list;

	create_redirection(pipex, cmd, cmd->token_list);
	dup_input_redirection(pipex, cmd);
	dup_output_redirection(pipex, cmd);
	if (create_argv(cmd->token_list, &argv) == FAILED)
		error_quit(pipex, NULL, 0);
	if (path_is_unset(pipex, &path_list))
		error_quit(pipex, *argv, 0);
	while (path_list != NULL)
		execute_file(&path_list, argv, envp);
	error_quit(pipex, *argv, CMD_NOT_FOUND);
}

int	evaluator(t_pipe *pipex, t_cmd *cmd, char **envp, int nb_of_cmds)
{
	int		i;
	pid_t	pid[nb_of_cmds];

	i = -1;
	while (++i < nb_of_cmds)
	{
		create_pipe(pipex, cmd);
		pid[i] = fork();
		cmd->token_list = pipex->token[i];
		if (pid[i] == FAILED)
			error_quit(pipex, NULL, 0);
		else if (pid[i] == CHILD_PROCESS)
			execution_child_process(pipex, cmd, envp);
		else if (pid[i] >= PARENT_PROCESS)
		{
			close(cmd->pipefd[1]);
			if (cmd->previous)
				close(cmd->pipefd[0]);
		}
		cmd = cmd->next;
	}
	return (last_child_status(pid[i - 1]));
}
