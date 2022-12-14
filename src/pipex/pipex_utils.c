/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 12:56:19 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/09 20:05:37 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*get_cmd(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmd_tmp;

	if (!path || !path[0] || !cmd)
		pipex_error(0, "get_cmd");
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

char	**get_path(char **env)
{
	char	**ret;

	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!(*env))
		return (NULL);
	ret = ft_split(&env[0][5], ':');
	if (!ret)
		pipex_error(0, "pipex_init");
	return (ret);
}

int	wait_for(t_pipex pipex)
{
	int	status;

	waitpid(pipex.pid_2, &status, 0);
	wait(NULL);
	return (status);
}

void	setup_fd(int fd_1, int fd_2, int fd_3, int fd_4)
{
	dup2(fd_1, fd_2);
	dup2(fd_3, fd_4);
}

void	close_pipe(int pipefd[2])
{
	if (close(pipefd[0]) == -1)
		pipex_error(0, "close_pipe");
	if (close(pipefd[1]) == -1)
		pipex_error(0, "close_pipe");
}
