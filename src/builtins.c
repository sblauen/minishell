/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 01:49:51 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/30 03:20:39 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"

/*
**  Change the current working directory.
*/

int						_builtin_cd(const char *path)
{
	struct stat			sb;

	if (!chdir(path))
		return (0);
	if (stat(path, &sb) == -1)
		puterr("cd: no such file or directory: ", path);
	else if ((sb.st_mode & S_IFMT) != S_IFDIR)
		puterr("cd: not a directory: ", path);
	else if (!(sb.st_mode & S_IXOTH))
		puterr("cd: permission denied: ", path);
	return (1);
}

/*
**  Output the passed arguments to stdout.
**
**  If '-n' is passed as option, no trailing newline
**  will be outputted.
*/

int					_builtin_echo(const char **args)
{
	int				eol;

	if (*args && !ft_strcmp(*args, "-n"))
	{
		eol = 0;
		++args;
	}
	else
		eol = 1;
	while (*args && *(args + 1))
	{
		ft_putstr(*args++);
		ft_putchar(' ');
	}
	ft_putstr(*args);
	if (eol)
		ft_putchar('\n');
	return (0);
}
