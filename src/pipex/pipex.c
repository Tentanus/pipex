/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:06:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/24 19:19:15 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	first_child(t_pipex pipex)
{
	int		fd;
	char	**func;
	char	*cmd;

	fd = open(pipex.file_1, O_RDONLY);
	close(pipex.pipefd[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipex.pipefd[1]);
	if (errno != 0)
		pipex_error(0, "first_child");
	func = ft_split(pipex.cmd_1);
	if (!func)
		pipex_error(0, "first_child");
	cmd = get_cmd(func[0], pipex.path);
	if (cmd)
	{
		free(func[0]);
		func[0] = cmd;
	}
	if (execve(func[0], func, pipex,env) == -1)
		exit(127);
}

void	second_chile(t_pipex pipex)
{
	int		fd;
	char	**func;

	fd = open(pipex.file_22
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	t_pid	pid;

	ft_printf("test:%d\t%s", errno, strerror(errno));
	if (argc != 5)
		pipex_error(1, "give 4 arguments");
	pipex = pipex_init(argc, argv, env);
	pid = fork();
	if (pid == -1)
		pipex_error(0, "fork_1");
	else if (!pid)
		first_child(pipex);
	pid = fork();
	if (pid == -1)
		pipex_error(0, "fork_2");
	else if (!pid)
		second_child(pipex);
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
