/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:49:40 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/21 19:53:39 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int		bin_exec(char **cmd, char **path)
{
	int					ret;
	int					status;
	char				*filename;
	char				*bin;
	pid_t				pid;

	if (!ft_strcmp(cmd[0], "cd"))
		return (_builtin_cd(cmd[1]));
	else if (!ft_strcmp(cmd[0], "echo"))
		return (_builtin_echo((const char **)(cmd + 1)));
	ret = -1;
	pid = fork();
	bin = ft_strjoin("/", cmd[0]);
	if (!pid)
	{
		while (*path && ret == -1)
		{
			ret = 0;
			filename = ft_strjoin(*path, bin);
			ret = execve(filename, cmd, NULL);
			ft_memdel((void **)&filename);
			path++;
		}
		ft_memdel((void **)&bin);
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

int						main(UNUSED int argc, UNUSED char **argv, char **envp)
{
	char				*line;
	char				**cmd;
	char				**path;

	while (1)
	{
		ft_putstr("$> ");
		ft_gnl(STDIN_FILENO, &line);
		cmd = ft_strsplit(line, ' ');
		if ((path = get_path(envp)))
			bin_exec(cmd, path);
		ft_strtabdel(cmd);
		ft_strtabdel(path);
		if (ft_strstr(line, "exit") || ft_strstr(line, "quit"))
		{
			ft_memdel((void **)&line);
			break ;
		}
		ft_memdel((void **)&line);
	}
	return (0);
}
