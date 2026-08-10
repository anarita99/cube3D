/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:21:55 by adores            #+#    #+#             */
/*   Updated: 2026/08/04 11:34:59 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_big_line(char **map)
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

int	rectangularize_map(t_map *map)
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

static bool	is_char(char **map, int i, int j, char c)
{
	if (map[i][j + 1] == c || map[i][j - 1] == c \
|| map[i + 1][j] == c || map[i - 1][j] == c)
		return (true);
	return (false);
}

static bool	is_cell_valid(t_map map, int i, int j)
{
	if (j == 0 && (map.grid[i][j] != '1' && map.grid[i][j] != ' '))
		return (false);
	if (i == 0 || i == map.height - 1)
	{
		if (map.grid[i][j] != '1' && map.grid[i][j] != ' ' )
			return (false);
	}
	if (map.grid[i][j] == '0')
	{
		if (is_char(map.grid, i, j, ' ') || is_char(map.grid, i, j, '\0'))
			return (false);
	}
	if (map.grid[i][j] == 'E' || map.grid[i][j] == 'W' \
|| map.grid[i][j] == 'N' || map.grid[i][j] == 'S')
	{
		if (is_char(map.grid, i, j, ' '))
			return (false);
	}
	return (true);
}

bool	is_map_valid(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.grid[i])
	{
		j = 0;
		while (map.grid[i][j])
		{
			if (!is_cell_valid(map, i, j))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
