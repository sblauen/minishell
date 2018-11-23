/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:39:12 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/23 15:40:22 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	s = *name | (*(name + 1) << 8);
	while (*env)
	{
		if ((**env | (*(*env + 1) << 8)) == s
				&& !ft_strncmp(*env + 2, name + 2, l - 2) && (*env)[l] == '=')
			return ((char *)(*env + l + 1));
		++env;
	}
	return (NULL);
}
