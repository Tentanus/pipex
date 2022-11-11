/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 22:32:33 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/11 22:51:03 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	**get_path_in_env(env)
{
	char	**ret;

	while(strncmp(env, "PATH", 4))
		env++;
	ret = ft_split((env + 5), ':');
	return (ret);
}

t_pipex	pipex_init(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	pipex.path = get_path_in_env(env, &pipex);

}
