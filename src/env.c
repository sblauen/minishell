/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:39:12 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/28 19:27:25 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**  Return the value corresponding to the environment variable 'name'.
**
**  If an error occurs or 'name' is not found, NULL is returned.
**  If 'name' has more than one character, the two first one's will
**  be used. This should be more efficient.
*/

char					*envget(const char *name, const char **env)
{
	size_t				l;
	short				s;

	if (!env || !name || !*name)
		return (NULL);
	if (!*(name + 1))
	{
		while (*env)
		{
			if (**env == *name && *(*env + 1) == '=')
				return ((char *)(*env + 2));
			++env;
		}
		return (NULL);
	}
	l = ft_strlen(name);
	s = (short)(*name | (*(name + 1) << 8));
	while (*env)
	{
		if ((**env | (*(*env + 1) << 8)) == s
				&& !ft_strncmp(*env + 2, name + 2, l - 2) && (*env)[l] == '=')
			return ((char *)(*env + l + 1));
		++env;
	}
	return (NULL);
}

/*
**  Return the index corresponding to the environment variable 'name'.
**
**  If 'name' is not found, the index corresponds to the last pointer
**  of the array. Thus, a check for NULL, at the given index, is required
**  If 'name' has more than one character, the two first one's will
**  be used. This should be more efficient.
**  If an error occurs -1 will be returned.
*/

int						envget_id(const char *name, const char **env, int i)
{
	size_t				l;
	short				s;

	if (!env || !name || !*name)
		return (-1);
	if (!*(name + 1))
	{
		while (*(env + i))
		{
			if (**(env + i) == *name && *(*(env + i) + 1) == '=')
				return (i);
			++i;
		}
		return (i);
	}
	l = ft_strlen(name);
	s = (short)(*name | (*(name + 1) << 8));
	while (*(env + i))
	{
		if ((*env[i] | env[i][1] << 8) == s
				&& !ft_strncmp(env[i] + 2, name + 2, l - 2) && env[i][l] == '=')
			return (i);
		++i;
	}
	return (i);
}

/*
**  Return a copy of the array 'env'.
**
**  If an error occurs NULL will be returned.
*/

char					**cpyenv(const char **env)
{
	char				**ep;
	char				**cpy;
	size_t				len;

	if (!env)
		return (NULL);
	len = 0;
	ep = (char **)env;
	while (*ep++)
		++len;
	if (!(cpy = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	ep = (char **)env;
	while (*ep)
	{
		if (!(*cpy = ft_strdup(*ep)))
			return (NULL);
		++ep;
		++cpy;
	}
	*cpy = NULL;
	return (cpy - len);
}

/*
**  Updates the environment variables SHELL and SHLVL.
**
**  In an error occurs, they will be no changes.
*/

char					**cfgenv(char *av0, char ***env)
{
	char				*sh;
	char				*buf;
	char				**args;

	*env = cpyenv((const char **)*env);
	if ((buf = getcwd(NULL, 0)))
	{
		sh = (char *)malloc(sizeof(char)
				* (ft_strlen(buf) + ft_strlen(av0) + 1));
		ft_strcpy(sh, buf);
		ft_strcat(sh, av0 + 1);
		args = (char *[2]){"SHELL", sh};
		envset((const char **)args, env);
		free(sh);
		free(buf);
	}
	if ((buf = envget("SHLVL", (const char **)*env)))
	{
		buf = ft_uitoa(ft_atoi(buf) + 1);
		args = (char *[2]){"SHLVL", buf};
		envset((const char **)args, env);
		free(buf);
	}
	return (*env);
}
