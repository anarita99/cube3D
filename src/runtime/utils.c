/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 15:01:53 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/24 15:05:48 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

bool	is_wall_tile(t_map map, int x, int y)
{
	if (y < 0 || x < 0 || y >= map.height || x >= map.width)
		return (false);
	if (!map.grid[y] || map.grid[y][x] == '\0')
		return (false);
	return (map.grid[y][x] == '1');
}
