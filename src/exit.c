/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:03:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/08/11 14:43:34 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_parsing(t_data *data)
{
	close(data->fd);
	free(data->assets.no.path);
	free(data->assets.so.path);
	free(data->assets.we.path);
	free(data->assets.ea.path);
	ft_freearray(data->map.grid);
}

static void	cleanup_textures(t_data *data)
{
	if (data->assets.no.img.ptr)
		mlx_destroy_image(data->mlx, data->assets.no.img.ptr);
	if (data->assets.so.img.ptr)
		mlx_destroy_image(data->mlx, data->assets.so.img.ptr);
	if (data->assets.we.img.ptr)
		mlx_destroy_image(data->mlx, data->assets.we.img.ptr);
	if (data->assets.ea.img.ptr)
		mlx_destroy_image(data->mlx, data->assets.ea.img.ptr);
}

static void	cleanup_mlx(t_data *data)
{
	if (!(data->mlx))
		return ;
	cleanup_textures(data);
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	data->mlx = NULL;
}

void	cleanup_and_exit(int status_code, char *error_msg, t_data *data)
{
	if (data)
	{
		cleanup_mlx(data);
		cleanup_parsing(data);
	}
	if (status_code != 0)
	{
		ft_putendl_fd("Error", 2);
		if (error_msg)
			ft_putendl_fd(error_msg, 2);
	}
	exit(status_code);
}
