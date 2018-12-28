/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 22:54:45 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/28 19:34:51 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"

static inline void		path_check(char *const *cmd, char *const *env)
{
	char				**epath;
	char				*fpath;
	char				*bin;
	size_t				i;

	i = 0;
	bin = ft_strjoin("/", cmd[0]);
	if ((epath = ft_strsplit(envget("PATH", (const char **)env), ':')))
	{
		while (*(epath + i))
		{
			fpath = ft_strjoin(*(epath + i), bin);
			if (!access(fpath, F_OK))
			{
				if (!access(fpath, X_OK))
					execve(fpath, cmd, env);
				else
					puterr("minishell: permission denied: ", cmd[0]);
			}
			ft_memdel((void **)&fpath);
			++i;
		}
		ft_strtabdel(&epath);
	}
	ft_memdel((void **)&bin);
}

static inline int		bin_check(char *const *cmd, char *const *env)
{
	path_check(cmd, env);
	if (!access(cmd[0], F_OK))
	{
		if (!access(cmd[0], X_OK))
			execve(cmd[0], cmd, env);
		else
			puterr("minishell: permission denied: ", cmd[0]);
	}
	else
		puterr("minishell: command not found: ", cmd[0]);
	return (-1);
}

int						bin_exec(char *const *cmd, char *const *env)
{
	int					status;
	pid_t				pid;

	pid = fork();
	if (!pid)
	{
		bin_check(cmd, env);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_putendl_fd("minishell: could not fork()", STDERR_FILENO);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
