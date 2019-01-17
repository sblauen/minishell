/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:01:00 by sblauens          #+#    #+#             */
/*   Updated: 2019/01/16 22:50:47 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

void					puterr(const char *str, const char *err)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
}

void					prompt(void)
{
	char				*pwd;
	char				*buf;

	if ((pwd = getcwd(NULL, 0)))
	{
		buf = (char *)malloc((ft_strlen(pwd) + 5) * sizeof(char));
		buf = ft_strcpy(buf, pwd);
		free(pwd);
		buf = ft_strcat(buf, " $> ");
		ft_putstr(buf);
		free(buf);
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
		return (1);
	}
	else if (read(STDIN_FILENO, NULL, 0) < 0)
	{
		ft_putendl_fd("minishell: 'stdin' seems to be closed", STDERR_FILENO);
		return (1);
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
