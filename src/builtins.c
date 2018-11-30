/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 01:49:51 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/30 05:49:36 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include "minishell.h"

static inline int		chpwd(char ***env)
{
	int					r;
	char				*buf;
	char				**args;

	args = (char *[2]){"OLDPWD", _getenv("PWD", (const char **)*env)};
	if (_setenv((const char **)args, env) == -1)
		return (-1);
	buf = getcwd(NULL, 0);
	args = (char *[2]){"PWD", buf};
	r = _setenv((const char **)args, env);
	free(buf);
	return (r);
}

/*
**  Change the current working directory.
*/

int						_builtin_cd(const char *path, char ***env)
{
	struct stat			sb;

	if (!path)
		path = _getenv("HOME", (const char **)*env);
	else if (*path == '-' && !*(path + 1))
		path = _getenv("OLDPWD", (const char **)*env);
	if (!chdir(path))
		return (chpwd(env));
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
