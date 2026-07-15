/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:39:07 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/15 15:01:48 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static t_vector	get_ray_direction(t_data *data, size_t current_x)
{
	t_vector	ray_dir;
	double		camera_x;

	camera_x = 2.0 * current_x / data->width - 1.0;
	ray_dir.x = data->player.dir.x + data->plane.x * camera_x;
	ray_dir.y = data->player.dir.y + data->plane.y * camera_x;
	return (ray_dir);
}

static void	init_dda_x(t_data *data, t_raycast *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_distance.x = (data->player.loc.x - rc->map.x);
		rc->side_distance.x *= rc->delta_distance.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_distance.x = (rc->map.x + 1.0 - data->player.loc.x);
		rc->side_distance.x *= rc->delta_distance.x;
	}
}

static void	init_dda_y(t_data *data, t_raycast *rc)
{
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_distance.y = (data->player.loc.y - rc->map.y);
		rc->side_distance.y *= rc->delta_distance.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_distance.y = (rc->map.y + 1.0 - data->player.loc.y);
		rc->side_distance.y *= rc->delta_distance.y;
	}
}

t_raycast	init_raycast_data(t_data *data, size_t current_x)
{
	t_raycast	rc;

	rc.ray_dir = get_ray_direction(data, current_x);
	rc.delta_distance.x = fabs(1.0 / rc.ray_dir.x);
	rc.delta_distance.y = fabs(1.0 / rc.ray_dir.y);
	rc.map.x = (int)data->player.loc.x;
	rc.map.y = (int)data->player.loc.y;
	init_dda_x(data, &rc);
	init_dda_y(data, &rc);
	rc.side = false;
	return (rc);
}

void	dda_loop(t_raycast *rc, t_map map)
{
	while (true)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (rc->side_distance.x < rc->side_distance.y)
		{
			rc->side_distance.x += rc->delta_distance.x;
			rc->map.x += rc->step.x;
			rc->side = false;
		}
		else
		{
			rc->side_distance.y += rc->delta_distance.y;
			rc->map.y += rc->step.y;
			rc->side = true;
		}
		// Check if ray has hit a wall
		if (is_wall_tile(map, (int)rc->map.x, (int)rc->map.y))
			break ;
	}
}
