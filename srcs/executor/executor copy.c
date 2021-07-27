// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   executor.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: llecoq <llecoq@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/07/16 15:04:08 by llecoq            #+#    #+#             */
// /*   Updated: 2021/07/27 15:35:08 by llecoq           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../includes/pipex.h"

// int	argv_is_a_valid_path(char *argv, int *fd)
// {
// 	if (*argv == '/')
// 	{
// 		*fd = open(argv, O_RDONLY);
// 		if (*fd > 0)
// 		{
// 			close(*fd);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// // a changer, facile a faire peter
// char	*search_for_path(t_list *list, char *argv)
// {
// 	char	*path;
// 	int		fd;

// 	if (argv_is_a_valid_path(argv, &fd))
// 		return (ft_strdup(argv));
// 	while (list)
// 	{
// 		path = ft_strjoin(list->content, argv);
// 		fd = open(path, O_RDONLY);
// 		if (fd > 0)
// 		{
// 			close(fd);
// 			return (path);
// 		}
// 		free(path);
// 		list = list->next;
// 	}
// 	return (NULL);
// }

// // gerer ./run.sh + changer pour des execve a la place de search_path
// // ATTENTION si unset PATH
// void	execution(t_pipe *pipex, t_cmd *cmd, char **envp)
// {
// 	char	*path;
// 	char	**argv;

// 	argv = cmd->args;
// 	path = search_for_path(pipex->path, *argv);
// 	if (path)
// 	{
// 		close(cmd->pipefd[0]);
// 		dup2(cmd->pipefd[1], 1);
// 		close(cmd->pipefd[1]);
// 		execve(path, argv, envp);
// 	}
// 	else
// 		error_quit(pipex, *argv, 1);
// }

// // void	read_from_fd(t_pipe *pipex, t_cmd *cmd, int *pipefd)
// // {
// // 	char	buff[1024];

// // 	(void)pipex;
// // 	close(pipefd[1]);
// // 	read(pipefd[0], &buff, 1024);
// // 	dprintf(cmd->fd, "%s", buff);
// // 	close(pipefd[0]);
// // }

// // void	read_from_fd(t_pipe *pipex, t_cmd *cmd, int *pipefd)
// // {
// // 	char	*line;
// // 	int		res;
	
// // 	close(pipefd[1]);
// // 	res = 1;
// // 	while (res > 0)
// // 	{
// // 		res = get_next_line(pipefd[0], &line);
// // 		if (res == -1)
// // 			error_quit(pipex, NULL, 0);
// // 		write(cmd->fd, line, ft_strlen(line));
// // 		write(cmd->fd, "\n", 1);
// // 		free(line);
// // 	}
// // 	close(pipefd[0]);
// // }

// // void	evaluator(t_pipe *pipex, t_cmd *cmds, char **envp)
// // {
// // 	int		i;
// // 	t_cmd	*head;
// // 	pid_t	pid[pipex->cmds_nb];

// // 	head = cmds;
// // 	i = -1;
// // 	while (++i < pipex->cmds_nb)
// // 	{
// // 		while (cmds && !cmds->args)
// // 			cmds = cmds->next;
// // 		if (cmds->args)
// // 		{
// // 			pid[i] = fork();
// // 			if (pid[i] == -1)
// // 				error_quit(pipex, NULL, 0);
// // 			if (pid[i] == 0)
// // 				execution(pipex, cmds, envp);
// // 			else if (pid[i])
// // 				read_from_fd(pipex, cmds, cmds->pipefd);
// // 				// close(cmds->pipefd[1]);
// // 			cmds = cmds->next;
// // 		}
// // 	}
// 	// read_fd(pipex, )
// // }
