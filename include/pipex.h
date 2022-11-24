/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 01:05:49 by mweverli      #+#    #+#                 */
/*   Updated: 2022/11/24 19:19:21 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//		INCLUDES

# include <unistd.h>	//	ACCESS 	checks accesibility of filename by path
//							DUP    	Duplicates the given fd to the lowest possible fd
//							DUP2   	Duplicates the given fd to the given newfd
//							EXECVE 	Executes the program given as <PATHNAME>
//							FORK   	creates a new process by duplicating the calling process
//							PIPE   	creates a unidirectional pipe used for interprocess communication
//							UNLINK 	
# include <sys/wait.h>	//	WAIT   	
//							WAITPID	
# include <string.h>	//	strerror
# include <errno.h>

//			Personal Includes

# include <libft.h>

//			FORBIDEN Includes

# include <stdio.h>

//		MACROS

# define PRCS_CHILD 0
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
} t_pipex;

//		FUNCTIONS

void	pipex_error(int error_id, const char* inp);
t_pipex	pipex_init(int argc, char **argv, char **env);

#endif
