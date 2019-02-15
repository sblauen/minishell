/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:49:40 by sblauens          #+#    #+#             */
/*   Updated: 2019/02/15 17:27:31 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

static inline int		cmd_check(char ***cmd, char ***env)
{
	if (!ft_strcmp((*cmd)[0], "cd"))
		return (builtin_cd((const char *)(*cmd)[1], env));
	else if (!ft_strcmp((*cmd)[0], "echo"))
		return (builtin_echo((const char **)*cmd + 1));
	else if (!ft_strcmp((*cmd)[0], "pwd"))
		return (builtin_pwd((const char **)*cmd + 1));
	else if (!ft_strcmp((*cmd)[0], "env"))
		return (builtin_env((const char **)*cmd + 1, (const char **)*env));
	else if (!ft_strcmp((*cmd)[0], "setenv"))
		return (builtin_setenv((const char **)*cmd + 1, env));
	else if (!ft_strcmp((*cmd)[0], "unsetenv"))
		return (builtin_unsetenv((const char **)*cmd + 1, *env));
	else if (!ft_strcmp((*cmd)[0], "exit"))
	{
		if ((*cmd)[1])
			builtin_exit(ft_atoi((*cmd)[1]), cmd, env);
		else
			builtin_exit(EXIT_SUCCESS, cmd, env);
	}
	return (-1);
}

static inline void		exit_main(int ret, char ***cmd, char ***env)
{
	if (ret == 0)
	{
		ft_putstr("\r\033[0K");
		builtin_exit(EXIT_SUCCESS, NULL, env);
	}
	else if (ret == -1)
	{
		ft_putstr_fd("minishell: an error has occured\n", STDERR_FILENO);
		builtin_exit(EXIT_FAILURE, cmd, env);
	}
	else if (ret == -2)
	{
		builtin_exit(EXIT_FAILURE, cmd, env);
	}
}

int						cmd_send(char ***cmd, char ***env)
{
	int					ret;

	ret = 0;
	if (**cmd && cmd_check(cmd, env) == -1)
		ret = bin_check((char *const *)*cmd, (char *const *)*env,
							"minishell: ");
	if (ret == -1)
		exit_main(-1, cmd, env);
	else if (ret == -2)
		exit_main(-2, cmd, env);
	return (0);
}

int						cmd_split(char **line, char ***env)
{
	int					i;
	char				**cmd;

	i = 0;
	cmd = ft_strsplit_ws(*line);
	if (!cmd)
		return (-1);
	while (cmd[i])
	{
		cmd[i] = line_parse(cmd[i], (const char **)*env);
		++i;
	}
	if (!cmd_send(&cmd, env))
		ft_strtabdel(&cmd);
	return (0);
}

int						main(int argc, char **argv, char **envp)
{
	int					ret;
	char				*line;
	char				**env;

	if (signal(SIGINT, sigh_intprompt) == SIG_ERR || errors_check(argc) == -1)
		exit(EXIT_FAILURE);
	env = cfgenv(*argv, &envp);
	while (1)
	{
		prompt();
		if ((ret = ft_gnl(STDIN_FILENO, &line)) <= 0)
		{
			if (!line)
				continue ;
			exit_main(ret, NULL, &env);
		}
		if (ft_strchr(line, ';'))
			ret = line_split(&line, &env);
		else
			ret = cmd_split(&line, &env);
		ft_memdel((void **)&line);
		if (ret == -1)
			exit_main(ret, NULL, &env);
	}
	return (0);
}
