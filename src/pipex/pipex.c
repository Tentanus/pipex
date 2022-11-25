/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:06:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/25 19:23:19 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <stdio.h>

void	first_child(t_pipex pipex)
{
	int		fd;
	char	**func;
	char	*cmd;

	fd = open(pipex.file_1, O_RDONLY);
	close(pipex.pipefd[0]);
	close(STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	printf("%d\n%s\n", errno, strerror(errno));
	if (errno != 0)
		pipex_error(0, "first_child");
	func = ft_split(pipex.cmd_1, ' ');
	printf("test\n");
	if (!func)
		pipex_error(0, "first_child");
	cmd = get_cmd(func[0], pipex.path);
	free(func[0]);
	func[0] = cmd;
	if (execve(func[0], func, pipex.env) == -1)
		exit(127);
}

void	second_child(t_pipex pipex)
{
	int		fd;
	char	**func;
	char	*cmd;

	fd = open(pipex.file_2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	close(pipex.pipefd[1]);
	close(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	printf("%d\n%s\n", errno, strerror(errno));
	if (errno != 0)
		pipex_error(0, "second_child");
	printf("test\n");
	func = ft_split(pipex.cmd_2, ' ');
	if (!func)
		pipex_error(0, "second_child");
	cmd = get_cmd(func[0], pipex.path);
	free(func[0]);
	func[0] = cmd;
	if (execve(func[0], func, pipex.env) == -1)
		exit(127);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		status;

	if (argc != 5)
		pipex_error(1, "give 4 arguments");
	pipex = pipex_init(argv, env);
	pipex.pid = fork();
	if (pipex.pid == (size_t) -1)
		pipex_error(0, "fork_1");
	else if (!pipex.pid)
		first_child(pipex);
	pipex.pid = fork();
	if (pipex.pid == (size_t) -1)
		pipex_error(0, "fork_2");
	else if (!pipex.pid)
		second_child(pipex);
	status = wait_for(pipex);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	return (status);
}


/*
	int		p_fd[2];

	int		i;
	pid_t	pid;

//	pipex_init(argc, argv, envp);

	i = ft_atoi(argv[1]);
	if (i < 1 && argc > 1)
		pipex_error(1, "argument must be positive");
	printf("PARENT (%d) START:\n", getpid());
	if (pipe(p_fd) == -1)
		pipex_error(0, "pipe_cration");

	while (i--)
	{
		pid = fork();
		if (pid == -1)
			pipex_error(0, "fork");
		if (pid == PRCS_CHILD)
		{
			child_func(p_fd);
			printf("test\n");
		}
		else
			continue ;
	}

	while (1)
	{
		i = wait(NULL);
		if (i == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				pipex_error(0, "wait");
		}
		printf("CHILD (%d) killed\n", i);
	}
	printf("PARENT (%d) ENDS\n", getpid());
	return (0);
}
*/

//	test using the file [dev/random]
//
//	pipe_fd[0] = read-end of pipee
//	pipe_fd[1] = write-end of pipee
//
