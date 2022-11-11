/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:06:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/11 17:51:53 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv)
{
//	int		p_fd[2];
	int		i;
	pid_t	pid;

	while (argc--)
		printf("%d\t%s\n", argc, argv[argc]);
	i = ft_atoi(argv[1]);
	if (i > 1 || argc > 1)
		pipex_error(1, "argument must be positive");
	printf("PARENT START:\n");
//	if (pipe(p_fd) == -1)
//		pipex_error(0, "pipe_cration");
	while (i--)
	{
		pid = fork();
		if (pid == -1)
			pipex_error(0, "fork");
		if (pid == 0)
		{
			printf("CHILD(%ld): %d", (long) getpid(), i);
			exit(EXIT_SUCCESS);
		}
		else
			printf("PARENT with child (%ld)", (long) getpid());
	}
	return (0);
}
