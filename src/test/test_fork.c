/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:06:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/18 20:08:29 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	child_func(int *p_fd)
{
	if (close(p_fd[1] == -1))
		pipex_error(0, "close_fd child");
	printf("CHILD (%d): active\n", getpid());
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int		p_fd[2];
	int		i;
	pid_t	pid;

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
			child_func(p_fd);
		else
			continue ;
	}

	while (1)
	{
		if (wait(NULL) == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				pipex_error(0, "wait");
		}
		printf("CHILD (-) killed\n");
	}
	printf("PARENT (%d) ENDS\n", getpid());
	return (0);
}


//	test using the file [dev/random]
//
//	pipe_fd[0] = read-end of pipee
//	pipe_fd[1] = write-end of pipee
//
