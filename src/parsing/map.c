/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:59:09 by adores            #+#    #+#             */
/*   Updated: 2026/06/03 12:16:14 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*map_line(char *s1, char *s2)
{
	size_t	buffer_size;
	char	*dst;

	if (!s1)
		buffer_size = ft_strlen(s2) + 1;
	else
		buffer_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(buffer_size);
	if (!dst)
		return (NULL);
	if(s1 && s2)
	{
		ft_strlcpy(dst, s1, buffer_size);
		ft_strlcat(dst, s2, buffer_size);
	}
	else
		ft_strlcpy(dst, s2, buffer_size);
	free(s1);
	free(s2);
	return (dst);
}

char	**make_map_grid(char *line, int fd)
{
	char	**map;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		tmp = map_line(tmp, line);
		line = get_next_line(fd);
		if (!line)
			break;
	}
	map = ft_split(tmp, '\n');
	free(tmp);
	int i = 0;
	while(map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	return (map);
}
