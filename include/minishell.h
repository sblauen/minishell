/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:10:53 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/19 18:52:36 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include "libft.h"

# define UNUSED __attribute__((__unused__))


int						_builtin_cd(const char *path, char ***env);
int						_builtin_echo(const char **args);
void					_builtin_exit(char ***cmd, char ***env);
int						_builtin_pwd(const char **args);
int						_builtin_env(const char **args, const char **env);
int						_builtin_setenv(const char **args, char ***env);
int						_builtin_unsetenv(const char **args, char **env);
char					*_getenv(const char *name, const char **env);
int						_getenv_id(const char *name, const char **env, int i);
int						_setenv(const char **args, char ***env);
int						_unsetenv(const char *name, char **env);
char					**cpyenv(const char **env);
void					prompt(const char **env);
int						errors_check(int argc);
void					puterr(const char *str, const char *err);
int						bin_exec(char *const *cmd, char *const *env);
char					*line_parse(char *line, const char **env);

#endif
