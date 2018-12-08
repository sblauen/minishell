/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 13:32:27 by sblauens          #+#    #+#             */
/*   Updated: 2018/12/08 21:49:58 by sblauens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

char					*quote_d(char *cp)
{
	while (*(cp + 1) != '"' && *(cp + 1))
	{
		*cp = *(cp + 1);
		++cp;
	}
	ft_strcpy(cp, cp + 2);
	return (cp);
}

char					*line_parse(char *line)
{
	char				*tmp;

	tmp = line;
	while (*tmp)
	{
		if (*tmp == '\'')
			tmp = quote_s(tmp);
		else if (*tmp == '"')
			tmp = quote_d(tmp);
		else
			++tmp;
	}
	return (line);
}
