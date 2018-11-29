/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 11:09:07 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/30 00:48:32 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char		*setval(const char **args, char **var)
{
	size_t				len;

	if (var)
		free((void *)*var);
	len = ft_strlen(args[0]) + 2;
	if (args[1])
		len += ft_strlen(args[1]);
	if (!(*var = (char *)malloc(len * sizeof(char))))
		return (NULL);
	ft_strcat(ft_strcpy(*var, args[0]), "=");
	if (args[1])
		ft_strcat(*var, args[1]);
	return (*var);
}

static inline char		**addval(const char **args, char **env, int i)
{
	char				**tmp;

	if (!(tmp = (char **)malloc((i + 2) * sizeof(char *))))
		return (NULL);
	tmp[i + 1] = NULL;
	tmp[i] = NULL;
	tmp[i] = setval(args, tmp + i);
	while (i--)
		tmp[i] = env[i];
	free(env);
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
