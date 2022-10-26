/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:06:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/10/18 01:06:06 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char** argv, char** envp)
{
	int		pipefd[2];

	if (argc != 5)
		pipex_error(1, "./pipex <file1> <cmd1> <cmd2> <file2>");
	if (pipe(pipefd) == -1)
		pipex_error(0, "main");
	

}
