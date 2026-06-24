/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:39:36 by adores            #+#    #+#             */
/*   Updated: 2026/06/24 14:50:51 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Fake hardcoded map for testing
static const char	*g_world_map[] = {
	"111111111111111111111111",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100111000000000000000001",
	"100101000000000000000001",
	"100101000000000000000001",
	"100000000000111000000001",
	"100000000000101000000001",
	"100000000000101000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000E00000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"111111111111111111111111"
};

static int	get_player_info(t_data *data)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (data->map.grid[y][x] == 'N')
			{
				data->player.loc.x = x;
				data->player.loc.y = y;
				data->player.dir.x = 0.0;
				data->player.dir.y = -1.0;
				return (0);
			}

			if (data->map.grid[y][x] == 'S')
			{
				data->player.loc.x = x;
				data->player.loc.y = y;
				data->player.dir.x = 0.0;
				data->player.dir.y = 1.0;
				return (0);
			}

			if (data->map.grid[y][x] == 'E')
			{
				data->player.loc.x = x;
				data->player.loc.y = y;
				data->player.dir.x = 1.0;
				data->player.dir.y = 0.0;
				return (0);
			}

			if (data->map.grid[y][x] == 'W')
			{
				data->player.loc.x = x;
				data->player.loc.y = y;
				data->player.dir.x = -1.0;
				data->player.dir.y = 0.0;
				return (0);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

int	main(void)
{
	t_data		data;

	data.width = WIN_WIDTH;
	data.height = WIN_HEIGHT;
	data.map.grid = g_world_map;
	data.map.width = 24;
	data.map.height = 24;
	if (get_player_info(&data) == -1)
		return (1);
	game(&data);
	return (0);
}
