/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:54:38 by adores            #+#    #+#             */
/*   Updated: 2026/06/25 16:10:27 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_config *config, t_map *map, t_data *data)
{
	config->no_path = NULL;
	config->so_path = NULL;
	config->ea_path = NULL;
	config->we_path = NULL;
	config->f_rgb = -1;
	config->c_rgb = -1;
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	data->player.orientation = '\0'; 
}
