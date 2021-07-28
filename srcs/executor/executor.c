/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:04:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/28 12:16:00 by llecoq           ###   ########.fr       */
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

static void	execution_child_process(t_pipe *pipex, t_cmd *cmd, char **envp)
{
	char	*file;
	char	**argv;
	t_list	*path;

	path = pipex->path;
	create_redirection(pipex, cmd, cmd->token_list);
	create_argv(cmd->token_list, &argv);
	while (path)
	{
		file = ft_strjoin(path, *argv);
		execve(file, argv, envp);
		free (file);
		path = path->next;
	}
	error_quit(pipex, *argv, 0);
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