/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:59:09 by adores            #+#    #+#             */
/*   Updated: 2026/08/10 15:53:17 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_row_valid(char **map, t_data *data, int i)
{
	int	j;

	j = -1;
	while (map[i][++j])
	{
		if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == ' ')
			continue ;
		if (map[i][j] == 'W' || map[i][j] == 'E' \
|| map[i][j] == 'N' || map[i][j] == 'S')
		{
			if (data->player.init_orientation == '\0')
			{
				data->player.loc.y = i + 0.5;
				data->player.loc.x = j + 0.5;
				data->player.init_orientation = map[i][j];
				continue ;
			}
			else
				return (false);
		}
		return (false);
	}
	return (true);
}

bool	is_grid_valid(char **grid, t_data *data)
{
	int	i;

	i = -1;
	if (!grid)
		return (false);
	while (grid[++i])
	{
		if (!is_row_valid(grid, data, i))
			return (false);
	}
	if (data->player.init_orientation == '\0')
		return (false);
	return (true);
}

static bool	has_neighbor(char **map, int i, int j, char c)
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
		if (has_neighbor(map.grid, i, j, ' ') \
|| has_neighbor(map.grid, i, j, '\0'))
			return (false);
	}
	if (map.grid[i][j] == 'E' || map.grid[i][j] == 'W' \
|| map.grid[i][j] == 'N' || map.grid[i][j] == 'S')
	{
		if (has_neighbor(map.grid, i, j, ' '))
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
