/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:42:08 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/24 15:00:36 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	game(t_data *data)
{
	t_img	img;

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, GAME_TITLE);
	data->img = &img;
	data->img->img = mlx_new_image(data->mlx, data->width, data->height);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_len, &data->img->endian);
	data->plane.x = -data->player.dir.y;
	data->plane.y = data->player.dir.x;
	mlx_hook(data->win, DestroyNotify, NoEventMask, destroy_handler, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handler, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}
