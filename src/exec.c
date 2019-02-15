/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 22:54:45 by sblauens          #+#    #+#             */
/*   Updated: 2019/02/15 17:22:26 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

static inline int		run(const char *bin, char *const *cmd,
								char *const *env, const char *caller)
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
		puterr(caller, "could not fork()", NULL);
	}
	else
	{
		if (signal(SIGINT, sigh_intchild) == SIG_ERR)
			return (-1);
		wait(NULL);
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
	fpath = NULL;
	bin = ft_strjoin("/", cmd[0]);
	if ((epath = ft_strsplit(envget("PATH", (const char **)env), ':')))
	{
		while (*(epath + i))
		{
			fpath = ft_strjoin(*(epath + i), bin);
			if (!access(fpath, F_OK))
			{
				break ;
			}
			ft_memdel((void **)&fpath);
			++i;
		}
		ft_strtabdel(&epath);
	}
	ft_memdel((void **)&bin);
	return (fpath);
}

static inline int		rights_check(const char *bin, char *const *cmd,
										char *const *env, const char *caller)
{
	struct stat			sb;

	if (stat(bin, &sb) == -1)
	{
		return (0);
	}
	else if ((sb.st_mode & S_IFMT) == S_IFDIR)
	{
		puterr(caller, "cannot execute a directory: ", cmd[0]);
		return (0);
	}
	else if (!access(bin, X_OK))
	{
		return (run(bin, cmd, env, caller));
	}
	puterr(caller, "permission denied: ", cmd[0]);
	return (0);
}

int						bin_check(char *const *cmd, char *const *env,
									const char *caller)
{
	int					ret;
	char				*bin;

	ret = 0;
	if ((bin = path_check(cmd, env)))
	{
		ret = rights_check(bin, cmd, env, caller);
	}
	else if (!(bin = ft_strdup(cmd[0])))
	{
		return (-1);
	}
	else if (!access(bin, F_OK))
	{
		ret = rights_check(bin, cmd, env, caller);
	}
	else
	{
		puterr(caller, "command not found: ", cmd[0]);
	}
	ft_memdel((void **)&bin);
	return (ret);
}
