/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:21:55 by adores            #+#    #+#             */
/*   Updated: 2026/06/25 13:59:24 by adores           ###   ########.fr       */
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

int	put_map_rect(t_map *map)
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
				return (ft_putstr_fd(MALL_ERR, 2), 1);
			ft_memset(map_line, ' ', map->width);
			map_line[map->width] = '\0';
			ft_memcpy(map_line, map->grid[i], j);
			free(map->grid[i]);
			map->grid[i] = map_line;
		}
	}
	return (0);
}

int	is_char(char **map, int i, int j, char c)
{
	if (map[i][j + 1] == c || map[i][j - 1] == c \
|| map[i + 1][j] == c || map[i - 1][j] == c)
		return (1);
	return (0);
}

static int	check_errors(char **map, int i, int j, int height)
{
	if (j == 0 && (map[i][j] != '1' && map[i][j] != ' '))
		return (ft_putstr_fd("Error\n Invalid map.\n", 2), 1);
	if (i == 0 || i == height)
	{
		if (map[i][j] != '1' && map[i][j] != ' ' )
			return (ft_putstr_fd("Error\n Invalid map.\n", 2), 1);
	}
	if (map[i][j] == '0')
	{
		if (is_char(map, i, j, ' ') == 1 || is_char(map, i, j, '\0'))
			return (ft_putstr_fd("Error\n Invalid map.\n", 2), 1);
	}
	if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N' \
|| map[i][j] == 'S')
	{
		if (is_char(map, i, j, ' ') == 1)
			return (ft_putstr_fd("Error\n Invalid map.\n", 2), 1);
	}
	return (0);
}

int	is_map_valid(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_errors(map, i, j, height) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
