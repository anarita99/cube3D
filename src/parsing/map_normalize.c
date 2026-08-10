/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:21:55 by adores            #+#    #+#             */
/*   Updated: 2026/08/04 11:34:59 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	find_big_line(char **map)
{
	int	tmp;
	int	i;
	int	j;

	tmp = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > tmp)
			tmp = j;
		i++;
	}
	return (tmp);
}

int	normalize_map(t_map *map)
{
	int		i;
	int		j;
	char	*map_line;

	map->width = find_big_line(map->grid);
	i = -1;
	while (map->grid[++i])
	{
		j = 0;
		while (map->grid[i][j])
			j++;
		if (j != map->width)
		{
			map_line = malloc(sizeof(char) * (map->width + 1));
			if (!map_line)
				return (1);
			ft_memset(map_line, ' ', map->width);
			map_line[map->width] = '\0';
			ft_memcpy(map_line, map->grid[i], j);
			free(map->grid[i]);
			map->grid[i] = map_line;
		}
	}
	return (0);
}
