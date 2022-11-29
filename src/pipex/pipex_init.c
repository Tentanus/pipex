/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 22:32:33 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/29 15:38:51 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	**get_path(char **env)
{
	char	**ret;

	while (ft_strncmp(*env, "PATH", 4))
		env++;
	ret = ft_split(&env[0][5], ':');
	if (!ret)
		pipex_error(0, "pipex_init");
	return (ret);
}

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
	pipex.pid = 0;
	return (pipex);
}
