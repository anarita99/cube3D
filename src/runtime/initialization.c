/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/27 14:40:18 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_pointer(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		cleanup_and_exit(1, "Cannot initialize MiniLibX.", data);
}

void	init_mlx_window(t_data *data)
{
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

void	load_texture(t_data *data, t_texture *texture)
{
	texture->img.ptr = mlx_xpm_file_to_image(
			data->mlx,
			texture->path,
			&texture->width,
			&texture->height);
	if (texture->img.ptr == NULL)
		cleanup_and_exit(1, "Texture file doesn't exist.", data);
	texture->img.addr = mlx_get_data_addr(
			texture->img.ptr,
			&texture->img.bpp,
			&texture->img.line_len,
			&texture->img.endian);
}

void	init_camera_data(t_data *data)
{
	if (data->player.init_orientation == 'N')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = -1.0;
	}
	else if (data->player.init_orientation == 'S')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = 1.0;
	}
	else if (data->player.init_orientation == 'E')
	{
		data->player.dir.x = 1.0;
		data->player.dir.y = 0.0;
	}
	else if (data->player.init_orientation == 'W')
	{
		data->player.dir.x = -1.0;
		data->player.dir.y = 0.0;
	}
	data->plane.x = -data->player.dir.y;
	data->plane.y = data->player.dir.x;
}
