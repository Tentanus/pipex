/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/23 23:05:03 by mweverli      #+#    #+#                 */
/*   Updated: 2022/10/23 23:05:06 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>
#include <string.h>
#include <stdio.h>

void	pipex_error(int error_id, const char* inp)
{
	ft_putstr_fd("ERROR", 2);
	if (!error_id)
	{
		ft_putstr_fd(" in ", 2);
		ft_putstr_fd(inp, 2);
		ft_putstr_fd(":\n", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	else if (error_id == 1)
	{
		ft_putstr_fd(" :\n", 2);
		ft_putendl_fd(inp, 2);
	}
	exit(EXIT_FAILURE);
}

