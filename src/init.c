/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:54:38 by adores            #+#    #+#             */
/*   Updated: 2026/06/29 14:43:26 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data)
{
	data->assets.no_path = NULL;
	data->assets.so_path = NULL;
	data->assets.ea_path = NULL;
	data->assets.we_path = NULL;
	data->assets.floor_rgb = -1;
	data->assets.ceiling_rgb = -1;
	data->map.grid = NULL;
	data->map.height = 0;
	data->map.width = 0;
	data->fd = -1;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->plane.x = 0.0;
	data->plane.y = 0.0;
	data->player.loc.x = 0.0;
	data->player.loc.y = 0.0;
	data->player.dir.x = 0.0;
	data->player.dir.y = 0.0;
	data->player.orientation = '\0'; 
}
