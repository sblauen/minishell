/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 14:10:53 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/28 17:32:53 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int						builtin_cd(const char *path, char ***env);
int						builtin_echo(const char **args);
void					builtin_exit(int status, char ***cmd, char ***env);
int						builtin_pwd(const char **args);
int						builtin_env(const char **args, const char **env);
int						builtin_setenv(const char **args, char ***env);
int						builtin_unsetenv(const char **args, char **env);
char					*envget(const char *name, const char **env);
int						envget_id(const char *name, const char **env, int i);
int						envset(const char **args, char ***env);
int						envunset(const char *name, char **env);
char					**cfgenv(char *argv, char ***env);
char					**cpyenv(const char **env);
void					prompt(const char **env);
int						errors_check(int argc);
void					puterr(const char *str, const char *err);
int						bin_exec(char *const *cmd, char *const *env);
char					*line_parse(char *line, const char **env);

#endif
