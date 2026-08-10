/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:59:09 by adores            #+#    #+#             */
/*   Updated: 2026/08/10 15:53:17 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*map_line(char *s1, char *s2)
{
	size_t	buffer_size;
	char	*dst;

	if (!s1)
		buffer_size = ft_strlen(s2) + 1;
	else
		buffer_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(buffer_size);
	if (!dst)
		return (free(s1), free(s2), NULL);
	if (s1 && s2)
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

static int	check_newline(char	*tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n')
		{
			j = i + 1;
			while (tmp[j] == ' ')
				j++;
			if (tmp[j] == '\n')
			{
				while (tmp[j] == '\n' || tmp[j] == ' ')
					j++;
				if (tmp[j] != '\0')
					return (1);
			}
		}
		i++;
	}
	return (0);
}

char	**make_map_grid(char *line, int fd, t_map *map)
{
	char	**grid;
	char	*tmp;
	int		count;

	tmp = NULL;
	count = 0;
	while (1)
	{
		tmp = map_line(tmp, line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	if (check_newline(tmp) == 1)
		return (free(tmp), free(line), NULL);
	grid = ft_split(tmp, '\n');
	if (!grid)
		return (free(tmp), NULL);
	free(tmp);
	while (grid[count])
		count++;
	map->height = count;
	return (grid);
}
