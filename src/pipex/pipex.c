/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:06:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/28 18:24:56 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <stdio.h>

FILE *fp;

void	first_child(t_pipex pipex)
{
	int		fd;
	char	**arg;
	char	*cmd;

	fd = open(pipex.file_1, O_RDONLY);
	setup_fd(fd, STDIN_FILENO, pipex.pipefd[PIPE_WRITE], STDOUT_FILENO);
	close_pipe(pipex.pipefd);
	arg = ft_split(pipex.cmd_1, ' ');
	if (!arg)
		pipex_error(0, "first_child");
	cmd = get_cmd(arg[0], pipex.path);
	execve(cmd, arg, pipex.env);
	exit(127);
}
//follow fork mode

void	second_child(t_pipex pipex)
{
	int		fd;
	char	**arg;
	char	*cmd;

	fd = open(pipex.file_2, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	setup_fd(pipex.pipefd[0], STDIN_FILENO, fd, STDOUT_FILENO);
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

//	fp = fopen("fprintf.txt", "w");
	if (argc != 5)
		pipex_error(1, "give 4 arguments");
	pipex = pipex_init(argv, env);
	pipex.pid = fork();
//	printf("%u\t%s\n", pipex.pid, strerror(errno));
	if (pipex.pid == -1)
		pipex_error(0, "fork_1");
	if (pipex.pid == 0)
		first_child(pipex);
	pipex.pid = fork();
	if (pipex.pid == -1)
		pipex_error(0, "fork_2");
	if (pipex.pid == 0)
		second_child(pipex);
	status = wait_for(pipex);
	waitpid(pipex.pid, &status, 0);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	fclose(fp);
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
