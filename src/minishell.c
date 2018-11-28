/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:49:40 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/28 01:39:39 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int		bin_exec(char **cmd, char **env)
{
	int					ret;
	int					status;
	char				*filename;
	char				*bin;
	char				**path;
	pid_t				pid;

	ret = -1;
	pid = fork();
	bin = ft_strjoin("/", cmd[0]);
	path = ft_strsplit(_getenv("PATH", (const char **)env), ':');
	if (!pid)
	{
		while (*path && ret == -1)
		{
			ret = 0;
			filename = ft_strjoin(*path, bin);
			ret = execve(filename, cmd, env);
			ft_memdel((void **)&filename);
			path++;
		}
		if (path)
			ft_strtabdel(path);
		ft_memdel((void **)&bin);
		if (ret)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd[0], 2);
		}
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

static inline int		cmd_check(char **cmd, char ***env)
{
	if (!ft_strcmp(cmd[0], "cd"))
		return (_builtin_cd(cmd[1]));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (_builtin_echo((const char **)(cmd + 1)));
	else if (!ft_strcmp(cmd[0], "setenv"))
		return (_builtin_setenv((const char **)(cmd + 1), env));
	else if (!ft_strcmp(cmd[0], "unsetenv"))
		return (_builtin_unsetenv((const char **)(cmd + 1), *env));
	return (-1);
}

int						main(UNUSED int argc, UNUSED char **argv, char **envp)
{
	char				*line;
	char				**cmd;
	char				**env;

	env = envp;
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
		if (cmd)
		{
			if (cmd_check(cmd, &env) == -1)
				bin_exec(cmd, env);
			ft_strtabdel(cmd);
		}
		ft_memdel((void **)&line);
	}
	return (0);
}
