/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:01:00 by sblauens          #+#    #+#             */
/*   Updated: 2019/02/15 17:09:56 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

void					puterr(const char *s, const char *err, const char *cmd)
{
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	if (err)
		ft_putstr_fd(err, STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
}

void					prompt(void)
{
	char				*pwd;
	char				*buf;

	if ((pwd = getcwd(NULL, 0)))
	{
		if ((buf = (char *)malloc((ft_strlen(pwd) + 5) * sizeof(char))))
		{
			buf = ft_strcpy(buf, pwd);
			buf = ft_strcat(buf, " $> ");
			ft_putstr(buf);
			free(buf);
		}
		free(pwd);
	}
	else
		ft_putstr("$> ");
}

int						errors_check(int argc)
{
	if (argc > 1)
	{
		ft_putendl_fd("minishell: options are not supported ... yet",
				STDERR_FILENO);
		return (-1);
	}
	else if (read(STDIN_FILENO, NULL, 0) < 0)
	{
		ft_putendl_fd("minishell: 'stdin' seems to be closed", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

void					sigh_intprompt(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		prompt();
	}
}

void					sigh_intchild(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
}
