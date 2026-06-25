/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:54:38 by adores            #+#    #+#             */
/*   Updated: 2026/06/25 13:31:42 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_configs(t_config *config, t_map *map)
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
}
