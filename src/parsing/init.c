/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:54:38 by adores            #+#    #+#             */
/*   Updated: 2026/06/11 14:21:59 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_configs(t_config *config, t_game *game)
{
	config->no_path = NULL;
	config->so_path = NULL;
	config->ea_path = NULL;
	config->we_path = NULL;
	config->f_rgb = -1;
	config->c_rgb = -1;
	game->map = NULL;
}
