/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:06:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/09 18:25:23 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	first_child(t_pipex pipex)
{
	int		fd;
	char	**arg;
	char	*cmd;

	pipex.pid_1 = fork();
	if (pipex.pid_1 == -1)
		pipex_error(0, "fork_1");
	if (pipex.pid_1 != 0)
		return ;
	fd = open(pipex.file_1, O_RDONLY);
	if (fd == -1)
		pipex_error(0, "first_child");
	setup_fd(fd, STDIN_FILENO, pipex.pipefd[PIPE_WRITE], STDOUT_FILENO);
	close_pipe(pipex.pipefd);
	arg = ft_split(pipex.cmd_1, ' ');
	if (!arg)
		pipex_error(0, "first_child");
	cmd = get_cmd(arg[0], pipex.path);
	execve(cmd, arg, pipex.env);
	exit(127);
}

void	second_child(t_pipex pipex)
{
	int		fd;
	char	**arg;
	char	*cmd;

	pipex.pid_2 = fork();
	if (pipex.pid_2 == -1)
		pipex_error(0, "fork_2");
	if (pipex.pid_2 != 0)
		return ;
	fd = open(pipex.file_2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		pipex_error(0, "second_child");
	setup_fd(pipex.pipefd[PIPE_READ], STDIN_FILENO, fd, STDOUT_FILENO);
	close_pipe(pipex.pipefd);
	arg = ft_split(pipex.cmd_2, ' ');
	if (!arg)
		pipex_error(0, "second_child");
	cmd = get_cmd(arg[0], pipex.path);
	execve(cmd, arg, pipex.env);
	exit(127);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		status;

	if (argc != 5)
		pipex_error(1, "give 4 arguments");
	pipex = pipex_init(argv, env);
	first_child(pipex);
	second_child(pipex);
	close_pipe(pipex.pipefd);
	status = wait_for(pipex);
	return (WEXITSTATUS(status));
}
