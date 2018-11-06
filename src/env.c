/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:39:12 by sblauens          #+#    #+#             */
/*   Updated: 2018/10/31 15:33:24 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**  Return a table containing the directories listed in the
**  environement variable PATH.
**
**  Each string and the table are dynamically allocated,
**  do not forget to free them.
*/

char					**get_path(char **env)
{
	while (*env)
	{
		if (**env == 'P' && *(*env + 1) == 'A' && *(*env + 2) == 'T'
				&& *(*env + 3) == 'H' && *(*env + 4) == '=')
			return (ft_strsplit(*env + 5, ':'));
		++env;
	}
	return (NULL);
}
