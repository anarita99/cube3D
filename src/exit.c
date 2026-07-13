/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:03:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/13 15:53:25 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_parsing(t_assets *assets, t_map *map)
{
	free(assets->no.path);
	free(assets->so.path);
	free(assets->we.path);
	free(assets->ea.path);
	ft_freearray(map->grid);
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

void	cleanup_and_exit(int status_code, const char *error_msg, t_data *data)
{
	cleanup_mlx(data);
	if (status_code != 0)
	{
		ft_printf("Error\n");
		if (error_msg)
			ft_printf("%s\n", error_msg);
	}
	cleanup_parsing(&data->assets, &data->map);
	exit(status_code);
}
