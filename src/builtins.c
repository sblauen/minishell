/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 01:49:51 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/21 19:49:29 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  Change the current working directory.
*/

int					_builtin_cd(const char *path)
{
	if (!access(path, F_OK))
	{
		if(!chdir(path))
			return (0);
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(path, 2);
		return (1);
	
	}
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(path, 2);
	return (1);
}

int					_builtin_echo(const char **args)
{
	while (*args && *(args + 1))
	{
		ft_putstr(*args++);
		ft_putchar(' ');
	}
	ft_putstr(*args);
	ft_putchar('\n');
	return (0);
}
