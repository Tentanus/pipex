/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 22:32:33 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/05 17:35:29 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_pipex	pipex_init(char **argv, char **env)
{
	t_pipex	pipex;

	pipex.file_1 = argv[1];
	pipex.cmd_1 = argv[2];
	pipex.cmd_2 = argv[3];
	pipex.file_2 = argv[4];
	pipex.env = env;
	pipex.path = get_path(env);
	if (pipe(pipex.pipefd) == -1)
		pipex_error(0, "pipex_init");
	pipex.pid_1 = 0;
	pipex.pid_2 = 0;
	return (pipex);
}
