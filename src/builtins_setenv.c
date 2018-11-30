/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 02:23:18 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/30 07:21:54 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void		printenv(const char **env)
{
	if (env)
		while (*env)
			ft_putendl(*env++);
}

/*
**  Builtin command to add or set a variable.
**
**  Returns 0 on succes and 1 on error.
*/

int						_builtin_setenv(const char **args, char ***env)
{
	if (args && !args[0])
		printenv((const char **)*env);
	else if ((args + 1) && args[1] && (args + 2) && args[2])
	{
		ft_putendl_fd("setenv: too many arguments\nUsage: VAR value", 2);
		return (1);
	}
	else if (_setenv(args, env) == -1)
		return (1);
	return (0);
}

/*
**  Builtin command to unset a variable.
**
**  Returns 0 on succes and 1 on error.
*/

int						_builtin_unsetenv(const char **args, char **env)
{
	if (!args || !*args)
	{
		ft_putendl_fd("unsetenv: too few arguments\nUsage: unsetenv VAR", 2);
		return (1);
	}
	if (_unsetenv(*args, env) == -1)
		return (1);
	return (0);
}
