/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:32:27 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/09 06:30:17 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char					*set_home(char *chrp, char **line, const char **env)
{
	char				*ret;
	char				*home;
	size_t				homelen;
	size_t				retlen;

	if (!(home = _getenv("HOME", env)))
		return (chrp + 1);
	homelen = ft_strlen(home);
	ret = (char *)malloc((ft_strlen(*line) + homelen) * sizeof(char));
	retlen = ft_strlcpy(ret, *line, (chrp - *line) + 1);
	retlen = ft_strlcat(ret, home, retlen + homelen);
	ft_strcat(ret, chrp + 1);
	free((void *)*line);
	*line = ret;
	return (*line + retlen);
}

char					*quote_s(char *cp)
{
	while (*(cp + 1) != '\'' && *(cp + 1))
	{
		*cp = *(cp + 1);
		++cp;
	}
	ft_strcpy(cp, cp + 2);
	return (cp);
}

char					*quote_d(char *cp, char **line, const char **env)
{
	while (*(cp + 1) != '"' && *(cp + 1))
	{
		*cp = *(cp + 1);
		++cp;
	}
	ft_strcpy(cp, cp + 2);
	return (cp);
}

char					*line_parse(char *line, const char **env)
{
	char				*tmp;

	tmp = line;
	while (*tmp)
	{
		if (*tmp == '\'')
			tmp = quote_s(tmp);
		else if (*tmp == '"')
			tmp = quote_d(tmp, &line, env);
		else if (*tmp == '~')
			tmp = set_home(tmp, &line, env);
		else
			++tmp;
	}
	return (line);
}
