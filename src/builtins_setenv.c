/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 02:23:18 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/27 10:38:52 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void		printenv(const char **env)
{
	if (env)
		while (*env)
			ft_putendl(*env++);
}

static inline char		*setval(const char **args, char **var)
{
	size_t				len;

	/* free((void *)*var); */
	len = ft_strlen(args[0]) + ft_strlen(args[1]) + 2;
	if (!(*var = (char *)malloc(len * sizeof(char))))
		return (NULL);
	ft_strcat(ft_strcat(ft_strcpy(*var, args[0]), "="), args[1]);
	return (*var);
}

static inline char		**addval(const char **args, char **env, int i)
{
	char				**tmp;

	if (!(tmp = (char **)malloc((i + 2) * sizeof(char *))))
		return (NULL);
	while (*env)
	{
		*tmp++ = *env++;
		/* free(*env); */
	}
	/* free(env - i); */
	*tmp = setval(args, tmp);
	*(tmp + 1) = NULL;
	tmp -= i;
	return (tmp);
}

/*
**  Set the environ variable 'args[0]' to the value 'args[1]'.
**
**  If the variable does not exist, it will be appended.
**  Returns 0 on succes and -1 on error.
*/

int						_setenv(const char **args, char ***env)
{
	char				*name;
	int					i;

	name = (char *)args[0];
	if (!*env || !name || !*name)
		return (-1);
	if ((i = _getenv_id(args[0], (const char **)*env, 0)) == -1)
		return (-1);
	if ((*env)[i])
		(*env)[i] = setval(args, *env + i);
	else
		*env = addval(args, *env, i);
	return (0);
}

/*
**  Unset the environ variable 'name'
**
**  Returns 0 on succes and -1 on error.
*/

int						_unsetenv(const char *name, char **env)
{
	int					i;

	if (!name || !*name)
		return (-1);
	if ((i = _getenv_id(name, (const char **)env, 0)) == -1)
		return (-1);
	env += i;
	/* free(*env); */
	while (*env)
	{
		*env = *(env + 1);
		++env;
	}
	return (0);
}

/*
**  Builtin command to add or set a variable.
**
**  Returns 0 on succes and 1 on error.
*/

int						_builtin_setenv(const char **opt, char ***env)
{
	if (opt && !opt[0])
	{
		printenv((const char **)*env);
		return (0);
	}
	else if (opt + 2 && opt[2])
	{
		ft_putendl_fd("setenv: too many arguments\nUsage: VAR value", 2);
		return (1);
	}
	if (_setenv(opt, env) == -1)
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
