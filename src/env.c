/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:39:12 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/21 17:47:06 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**  Return the value corresponding to the environment variable 'name'.
**
**  If an error occurs or 'name' is not found, NULL is returned.
**  If 'name' has more than one character, the two first one's will
**  be used. This should be more efficient.
*/

char					*_getenv(const char *name, const char **env)
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

int						_getenv_id(const char *name, const char **env, int i)
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
