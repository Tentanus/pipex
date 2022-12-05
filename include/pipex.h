/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:05:49 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/02 11:18:14 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//		INCLUDES

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

//			Personal Includes

# include <libft.h>

//		MACROS

# define PIPE_READ 0
# define PIPE_WRITE 1 

//		STRUCTURES

typedef struct s_pipex{
	char	*cmd_1;
	char	*cmd_2;
	char	*file_1;
	char	*file_2;
	char	**env;
	char	**path;
	int		pipefd[2];
	pid_t	pid_1;
	pid_t	pid_2;
}	t_pipex;

//		FUNCTIONS

void	pipex_error(int error_id, const char *inp);
t_pipex	pipex_init(char **argv, char **env);

//	Utils

char	*get_cmd(char *cmd, char **path);
char	**get_path(char **env);
int		wait_for(t_pipex pipex);
void	setup_fd(int fd_1, int fd_2, int fd_3, int fd_4);
void	close_pipe(int pipefd[2]);

#endif
