/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:59:09 by adores            #+#    #+#             */
/*   Updated: 2026/06/02 15:47:44 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*map_line(char *s1, char *s2)
{
	size_t	buffer_size;
	char	*dst;

	if (!s2)
		buffer_size = ft_strlen(s1) + 1;
	else if (!s1)
		buffer_size = ft_strlen(s2) + 1;
	else
		buffer_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(buffer_size);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, buffer_size);
	ft_strlcat(dst, s2, buffer_size);
	free(s1);
	free(s2);
	return (dst);
}

char	**make_map_grid(char *line, t_game game)
{
	char	**map;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		tmp = map_line(line, tmp);
		line = get_next_line(game.fd);
		if (!line)
			break;
		free(line);
	}
	map = ft_split(tmp, '\n');
	free(tmp);
	int i = 0;
	while(map[i])
	{
		printf("%s", map[i]);
		i++;
	}
	return (map);
}
