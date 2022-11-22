/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 16:21:54 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/21 18:02:01 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <stddef.h>

int main(int argc, char **argv, char *env[])
{
	int		pipefd[2];
	size_t	pid;
	char	*args[3] = {"./test1", argv[1], NULL};

	if (argc != 2)
		return (0);
	if (pipe(pipefd) == -1)
		pipex_error(0, "pipe");
	if ((pid = fork()) == -1)
		pipex_error(0, "fork");
	if (pid == 0)
	{
		close(pipefd[0]);				//close Pipe read end
		close(STDOUT_FILENO);			//close STD_OUT
		dup2(pipefd[1], STDOUT_FILENO);	//put Pipe write end on STD_OUT
		close(pipefd[1]);				//close pipe write end
		execve("test1", args, env);
		exit(1000);
	}

	if ((pid = fork()) == -1)
		pipex_error(0, "fork");
	if (pid == 0)
	{
		close(pipefd[1]);				//close Pipe write end
		close(0);						//close STD_IN
		dup2(pipefd[0], 0);				//put Pipe read end on STD_IN
		close(pipefd[0]);				//close pipe read end
		execve("test2", NULL, env);
		exit(2000);
	}

	while(1)
	{
		if (wait(NULL) == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				pipex_error(0, "wait");
		}
	}
	printf("Parent Ends\n");
	return (0);
}
