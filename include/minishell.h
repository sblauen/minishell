/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:10:53 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/27 06:19:52 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include "libft.h"

# define UNUSED __attribute__((__unused__))

int						_builtin_cd(const char *path);
int						_builtin_echo(const char **args);
char					*_getenv(const char *name, const char **env);
int						_getenv_id(const char *name, const char **env, int i);

#endif
