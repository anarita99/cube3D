/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:42:08 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/17 15:54:55 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	data.player.loc.x = 1.0;
	data.player.loc.y = 1.0;
	data.player.dir.x = 0.0;
	data.player.dir.y = 1.0;
	data.plane.x = 1.0;
	data.plane.y = 0.0;

	mlx_hook(data.win, DESTROY_EVENT, NO_MASK, destroy_handler, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_loop(data.mlx);
}
