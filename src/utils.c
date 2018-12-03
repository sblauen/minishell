/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:01:00 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/03 03:02:22 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					puterr(const char *str, const char *err)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
}

void					prompt(const char **env)
{
	char				*pwd;
	char				*buf;

	if ((pwd = _getenv("PWD", env)))
	{
		buf = (char *)malloc((ft_strlen(pwd) + 5) * sizeof(char));
		buf = ft_strcpy(buf, pwd);
		buf = ft_strcat(buf, " $> ");
		ft_putstr(buf);
		free(buf);
	}
	else
		ft_putstr("$> ");
}
