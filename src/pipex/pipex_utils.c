/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 12:56:19 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/29 15:38:50 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*get_cmd(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmd_tmp;

	if (!ft_strncmp(cmd, "./", 2))
		if (access(cmd, X_OK | F_OK) == -1)
			pipex_error(0, "get_cmd");
	i = 0;
	cmd_tmp = ft_strjoin("/", cmd);
	while (path[i] != NULL)
	{
		cmd_path = ft_strjoin(path[i], cmd_tmp);
		if (access(cmd_path, X_OK | F_OK) == 0)
			return (free(cmd), cmd_path);
		free(cmd_path);
		i++;
	}
	free(cmd_tmp);
	return (cmd);
}

int	wait_for(t_pipex pipex)
{
	int	status;
	int	i;

	waitpid(pipex.pid, &status, 0);
	while (1)
	{
		i = wait(NULL);
		if (i == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				pipex_error(0, "wait_for");
		}
	}
	return (status);
}

void	setup_fd(int fd_1, int fd_2, int fd_3, int fd_4)
{
	if (dup2(fd_1, fd_2) == -1)
		pipex_error(0, "setup_fd");
	if (dup2(fd_3, fd_4) == -1)
		pipex_error(0, "setup_fd");
}

void	close_pipe(int pipefd[2])
{
	if (close(pipefd[0]) == -1)
		pipex_error(0, "close_pipe");
	if (close(pipefd[1]) == -1)
		pipex_error(0, "close_pipe");
}
