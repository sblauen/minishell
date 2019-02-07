/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:32:27 by sblauens          #+#    #+#             */
/*   Updated: 2019/02/07 22:46:06 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**  Modify the character pointed to by 'chrp' to the home's value.
**
**  Returns a pointer to the character following the last
**  one of the home's path.
*/

static inline char		*set_home(char *chrp, char **line, const char **env)
{
	char				*ret;
	char				*home;
	size_t				homelen;
	size_t				retlen;

	if (!(home = envget("HOME", env)))
		return (chrp + 1);
	homelen = ft_strlen(home);
	if (!(ret = (char *)malloc((ft_strlen(*line) + homelen) * sizeof(char))))
		return (chrp + 1);
	retlen = ft_strlcpy(ret, *line, (chrp - *line) + 1);
	retlen = ft_strlcat(ret, home, retlen + homelen);
	ft_strcat(ret, chrp + 1);
	free((void *)*line);
	*line = ret;
	return (*line + retlen);
}

/*
**  Modify the variable pointed to by 'chrp' with its value.
**
**  Returns a pointer to the character following the last
**  one of the variable's value.
**  The three values contained in 'len[3]' are respectively
**  the variable, the value and the return length.
*/

static inline char		*set_var(char *chrp, char **line, const char **env)
{
	char				*tmp;
	char				*val;
	size_t				len[3];

	len[0] = 0;
	while (chrp + len[0] + 1 && ft_isalnum(chrp[len[0] + 1]))
		++len[0];
	if (!(tmp = (char *)malloc((len[0] + 1) * sizeof(char))))
		return (chrp + 1);
	ft_strlcpy(tmp, chrp + 1, len[0] + 1);
	val = envget(tmp, env);
	free(tmp);
	if (val)
	{
		len[1] = ft_strlen(val);
		if (!(tmp = (char *)malloc((ft_strlen(*line) + len[1]) * sizeof(char))))
			return (chrp + 1);
		len[2] = ft_strlcpy(tmp, *line, (chrp - *line) + 1);
		len[2] = ft_strlcat(tmp, val, len[2] + len[1]);
		ft_strcat(tmp, chrp + len[0] + 1);
		free((void *)*line);
		*line = tmp;
		return (*line + len[2]);
	}
	return (chrp + 1);
}

char					*line_parse(char *line, const char **env)
{
	char				*tmp;

	tmp = line;
	while (*tmp)
	{
		if (*tmp == '~')
			tmp = set_home(tmp, &line, env);
		else if (*tmp == '$')
			tmp = set_var(tmp, &line, env);
		else
			++tmp;
	}
	return (line);
}
