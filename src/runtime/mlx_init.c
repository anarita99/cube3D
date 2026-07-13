/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/13 16:10:26 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		cleanup_and_exit(1, "Cannot initialize MiniLibX.", data);
	data->win = mlx_new_window(
			data->mlx, data->width, data->height, GAME_TITLE);
	if (!data->win)
		cleanup_and_exit(1, "Cannot create window.", data);
}

void	init_render_image(t_data *data)
{
	data->img.ptr = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->img.ptr)
		cleanup_and_exit(1, "Cannot create image.", data);
	data->img.addr = mlx_get_data_addr(
			data->img.ptr,
			&data->img.bpp,
			&data->img.line_len,
			&data->img.endian);
	if (!data->img.addr)
		cleanup_and_exit(1, "Cannot access image data.", data);
}

static void	load_texture(t_texture *texture, void *mlx)
{
	texture->img.ptr = mlx_xpm_file_to_image(
			mlx,
			texture->path,
			&texture->width,
			&texture->height);
	texture->img.addr = mlx_get_data_addr(
			texture->img.ptr,
			&texture->img.bpp,
			&texture->img.line_len,
			&texture->img.endian);
}

void	load_textures(t_data *data)
{
	load_texture(&data->assets.no, data->mlx);
	load_texture(&data->assets.so, data->mlx);
	load_texture(&data->assets.we, data->mlx);
	load_texture(&data->assets.ea, data->mlx);
}
