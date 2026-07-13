/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:54:38 by adores            #+#    #+#             */
/*   Updated: 2026/07/13 15:39:07 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_texture(t_texture *texture)
{
	texture->path = NULL;
	texture->width = TEXTURE_RES;
	texture->height = TEXTURE_RES;
}

void	init(t_data *data)
{
	init_texture(&data->assets.no);
	init_texture(&data->assets.so);
	init_texture(&data->assets.we);
	init_texture(&data->assets.ea);
	data->assets.floor_rgb = -1;
	data->assets.ceiling_rgb = -1;
	data->map.grid = NULL;
	data->map.height = 0;
	data->map.width = 0;
	data->fd = -1;
	data->mlx = NULL;
	data->win = NULL;
	data->plane.x = 0.0;
	data->plane.y = 0.0;
	data->player.loc.x = 0.0;
	data->player.loc.y = 0.0;
	data->player.dir.x = 0.0;
	data->player.dir.y = 0.0;
	data->player.orientation = '\0'; 
}
