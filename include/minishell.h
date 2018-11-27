/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:10:53 by sblauens          #+#    #+#             */
/*   Updated: 2018/11/27 10:16:21 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include "libft.h"

# define UNUSED __attribute__((__unused__))

int						_builtin_cd(const char *path);
int						_builtin_echo(const char **args);
int						_builtin_setenv(const char **opt, char ***env);
int						_builtin_unsetenv(const char **args, char **env);
char					*_getenv(const char *name, const char **env);
int						_getenv_id(const char *name, const char **env, int i);

#endif
