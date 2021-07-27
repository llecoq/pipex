/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 15:04:08 by llecoq            #+#    #+#             */
/*   Updated: 2021/07/27 17:29:01 by llecoq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

// static int	valid_redirection(t_token *token_list)
// {
	
// }

static void	execution_child_process(t_pipe *pipex, t_cmd *cmd, char **envp)
{
	char	*path;
	char	**argv;

	(void)envp;
	(void)path;
	(void)argv;
	if (create_redirection(pipex, cmd, cmd->token_list) == IS_VALID)
	{
	}
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