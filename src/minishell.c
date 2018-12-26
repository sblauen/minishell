/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:49:40 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/21 18:13:10 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if ((epath = ft_strsplit(_getenv("PATH", (const char **)env), ':')))
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

static inline int		cmd_check(char ***cmd, char ***env)
{
	if (!ft_strcmp((*cmd)[0], "cd"))
		return (_builtin_cd((const char *)(*cmd)[1], env));
	else if (!ft_strcmp((*cmd)[0], "echo"))
		return (_builtin_echo((const char **)*cmd + 1));
	else if (!ft_strcmp((*cmd)[0], "pwd"))
		return (_builtin_pwd((const char **)*cmd + 1));
	else if (!ft_strcmp((*cmd)[0], "env"))
		return (_builtin_env((const char **)*cmd + 1, (const char **)*env));
	else if (!ft_strcmp((*cmd)[0], "setenv"))
		return (_builtin_setenv((const char **)*cmd + 1, env));
	else if (!ft_strcmp((*cmd)[0], "unsetenv"))
		return (_builtin_unsetenv((const char **)*cmd + 1, *env));
	else if (!ft_strcmp((*cmd)[0], "exit"))
		_builtin_exit(cmd, env);
	return (-1);
}

int						main(int argc, UNUSED char **argv, char **envp)
{
	char				*line;
	char				**cmd;
	char				**env;

	if (errors_check(argc) == 1)
		return (1);
	env = cfgenv(&envp);
	while (1)
	{
		prompt((const char **)env);
		if (ft_gnl(STDIN_FILENO, &line) < 0)
		{
			if (!line)
				continue ;
			ft_putendl_fd("minishell: an error has occured", STDERR_FILENO);
			break ;
		}
		line = line_parse(line, (const char **)env);
		cmd = ft_strsplit_ws(line);
		ft_memdel((void **)&line);
		if (cmd && *cmd)
			if (cmd_check(&cmd, &env) == -1)
				bin_exec((char *const *)cmd, env);
		if (cmd)
			ft_strtabdel(&cmd);
	}
	return (0);
}
