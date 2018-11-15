/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 01:49:51 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/15 04:00:57 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					_builtin_cd(const char *path)
{
	if (!access(path, X_OK)) 
	{
		if(!chdir(path))
			return ;
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(path, 2);
		return ;
	
	}
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(path, 2);

}
