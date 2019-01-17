/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 22:54:45 by sblauens          #+#    #+#             */
/*   Updated: 2019/01/17 09:19:02 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

static inline int		run(const char *bin, char *const *cmd,
								char *const *env)
{
	pid_t				pid;

	pid = fork();
	if (!pid)
	{
		execve(bin, cmd, env);
		return (-2);
	}
	else if (pid < 0)
	{
		ft_putendl_fd("minishell: could not fork()", STDERR_FILENO);
	}
	else
	{
		if (signal(SIGINT, sigh_intchild) == SIG_ERR)
			return (-1);
		wait(NULL);
		ft_memdel((void **)&bin);
		if (signal(SIGINT, sigh_intprompt) == SIG_ERR)
			return (-1);
	}
	return (0);
}

static inline char		*path_check(char *const *cmd, char *const *env)
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
					break ;
				puterr("minishell: permission denied: ", cmd[0]);
			}
			ft_memdel((void **)&fpath);
			++i;
		}
		ft_strtabdel(&epath);
	}
	ft_memdel((void **)&bin);
	return (fpath);
}

int						bin_check(char *const *cmd, char *const *env)
{
	char				*bin;

	if ((bin = path_check(cmd, env)))
		return (run(bin, cmd, env));
	if (!(bin = ft_strdup(cmd[0])))
		return (-1);
	if (!access(bin, F_OK))
	{
		if (!access(bin, X_OK))
			return (run(bin, cmd, env));
		else
			puterr("minishell: permission denied: ", bin);
	}
	else
		puterr("minishell: command not found: ", bin);
	ft_memdel((void **)&bin);
	return (0);
}
