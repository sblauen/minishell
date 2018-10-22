/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:49:40 by sblauens          #+#    #+#             */
/*   Updated: 2018/10/21 19:14:30 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int		bin_exec(char **cmd)
{
	char				*bin;
	pid_t				pid;
	/* pid_t				wpid; */
	int					status;

	pid = fork();
	if (!pid)
	{
		bin = ft_strjoin("/bin/", cmd[0]);
		execve(bin, cmd, NULL);
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

int						main(void)
{
	char				*line;
	char				**cmd;

	while (1)
	{
		ft_putstr("$> ");
		ft_gnl(STDIN_FILENO, &line);
		cmd = ft_strsplit(line, ' ');
		bin_exec(cmd);
		ft_strtabdel(cmd);
		if (ft_strstr(line, "exit") || ft_strstr(line, "quit"))
		{
			ft_memdel((void **)&line);
			break ;
		}
		ft_memdel((void **)&line);
	}
	return (0);
}
