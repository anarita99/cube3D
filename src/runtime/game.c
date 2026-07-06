/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:42:08 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/01 15:43:31 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	game(t_data *data)
{
	t_img	img;

	data->mlx = mlx_init();
	if (!data->mlx)
		cleanup_and_exit(1, "Cannot initialize MiniLibX.", data);
	data->win = mlx_new_window(data->mlx, data->width, data->height, GAME_TITLE);
	if (!data->win)
		cleanup_and_exit(1, "Cannot create window.", data);
	data->img = &img;
	data->img->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img->img)
		cleanup_and_exit(1, "Cannot create image.", data);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bits_per_pixel, &data->img->line_len, &data->img->endian);
	if (!data->img->addr)
		cleanup_and_exit(1, "Cannot access image data.", data);

	data->assets.ea.img.img = mlx_xpm_file_to_image(data->mlx, data->assets.ea.path, &data->assets.ea.width, &data->assets.ea.height);
	data->assets.ea.img.addr = mlx_get_data_addr(data->assets.ea.img.img, &data->assets.ea.img.bits_per_pixel, &data->assets.ea.img.line_len, &data->assets.ea.img.endian);
		
	mlx_hook(data->win, DestroyNotify, NoEventMask, destroy_handler, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handler, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}
