/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_pipe.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 16:21:54 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/18 20:08:18 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int main(int argc, char *argv[], char *env[])
{
	int		pipefd[2];
	size_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		pipex_error(0, "pipe");
	pid = fork();
	if (pid == -1)
		pipex_error(0, "fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		close(STDOUT_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(test, NULL, env);
		exit(1000);
	}

	waitpid(pid, &status, WUNTRACED);

	pid = fork();
	if (pid == -1)
		pipex_error(0, "fork");
	if (pid == 0)
	{
		close(pipefd[1]);
		close(0);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		execve(test, NULL, env);
		exit(1000);
	}



}
