/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_setenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 02:23:18 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/27 06:37:22 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

