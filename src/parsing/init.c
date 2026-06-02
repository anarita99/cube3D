/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 15:54:38 by adores            #+#    #+#             */
/*   Updated: 2026/06/02 14:43:12 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_configs(t_config *config)
{
	config->no_path = NULL;
	config->so_path = NULL;
	config->ea_path = NULL;
	config->we_path = NULL;
	config->f_rgb = -1;
	config->c_rgb = -1;
}
