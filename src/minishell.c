/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:49:40 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/02 07:56:48 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int		bin_check(char *const *cmd, char *const *env)
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
	}
	if (epath)
		ft_strtabdel(&epath);
	ft_memdel((void **)&bin);
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
		ft_putendl("Error: fork() unsuccesful.");
	}
	else
	{
		wait(&status);
	}
	return (0);
}

static inline int		cmd_check(const char **cmd, char ***env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (_builtin_cd(cmd[1], env));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (_builtin_echo(cmd + 1));
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (_builtin_pwd(cmd + 1));
	else if (!ft_strcmp(cmd[0], "env"))
		return (_builtin_env(cmd + 1, (const char **)*env));
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (_builtin_setenv(cmd + 1, env));
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		return (_builtin_unsetenv(cmd + 1, *env));
	return (-1);
}

int						main(UNUSED int argc, UNUSED char **argv, char **envp)
{
	char				*line;
	char				**cmd;
	char				**env;

	env = cpyenv((const char **)envp);
	while (1)
	{
		ft_putstr("$> ");
		ft_gnl(STDIN_FILENO, &line);
		if (ft_strstr(line, "exit") || ft_strstr(line, "quit"))
		{
			ft_memdel((void **)&line);
			break ;
		}
		cmd = ft_strsplit(line, ' ');
		if (cmd && *cmd)
			if (cmd_check((const char **)cmd, &env) == -1)
				bin_exec((char *const *)cmd, env);
		if (cmd)
			ft_strtabdel(&cmd);
		ft_memdel((void **)&line);
	}
	if (env)
		ft_strtabdel(&env);
	return (0);
}
