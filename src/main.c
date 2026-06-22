/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:42:08 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/22 15:07:51 by leramos-         ###   ########.fr       */
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
	"100000000000000000000001",
	"111111111111111111111111"
};

int	main(void)
{
	t_data	data;
	t_img	img;

	data.width = WIN_WIDTH;
	data.height = WIN_HEIGHT;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, GAME_TITLE);

	data.img = &img;
	data.img->img = mlx_new_image(data.mlx, data.width, data.height);
	data.img->addr = mlx_get_data_addr(data.img->img, &data.img->bits_per_pixel, &data.img->line_len, &data.img->endian);

	data.map.grid = g_world_map;
	data.map.width = 24;
	data.map.height = 24;
	
	data.player.loc.x = 1.0;
	data.player.loc.y = 1.0;
	data.player.dir.x = 0.0;
	data.player.dir.y = 1.0;
	data.plane.x = 1.0;
	data.plane.y = 0.0;

	mlx_hook(data.win, DestroyNotify, NoEventMask, destroy_handler, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_handler, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
}
