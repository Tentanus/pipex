/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/24 12:56:19 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/25 18:08:15 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*get_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(path[i], W_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (ft_strdup(cmd));
}

int	wait_for(t_pipex pipex)
{
	int	status;
	int	i;

	waitpid(pipex.pid, &status, 0);
	while (1)
	{
		i = wait(NULL);
		if (i == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				pipex_error(0, "wait_for");
		}
	}
	return (status);
}
