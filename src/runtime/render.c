/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:59:20 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/06 15:50:05 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static t_raycast_data	init_raycast_data(t_data *data, size_t current_x)
{
	t_raycast_data	rc;
	double			camera_x;

	camera_x = 2.0 * current_x / data->width - 1.0;
	rc.ray_dir.x = data->player.dir.x + data->plane.x * camera_x;
	rc.ray_dir.y = data->player.dir.y + data->plane.y * camera_x;
	rc.delta_distance.x = fabs(1.0 / rc.ray_dir.x);
	rc.delta_distance.y = fabs(1.0 / rc.ray_dir.y);
	rc.map.x = (int)data->player.loc.x;
	rc.map.y = (int)data->player.loc.y;
	if (rc.ray_dir.x < 0)
	{
		rc.step.x = -1;
		rc.side_distance.x = (data->player.loc.x - rc.map.x) * rc.delta_distance.x;
	}
	else
	{
		rc.step.x = 1;
		rc.side_distance.x = (rc.map.x + 1.0 - data->player.loc.x) * rc.delta_distance.x;
	}
	if (rc.ray_dir.y < 0)
	{
		rc.step.y = -1;
		rc.side_distance.y = (data->player.loc.y - rc.map.y) * rc.delta_distance.y;
	}
	else
	{
		rc.step.y = 1;
		rc.side_distance.y = (rc.map.y + 1.0 - data->player.loc.y) * rc.delta_distance.y;
	}
	rc.side = false;
	return (rc);
}

static void	dda_loop(t_raycast_data *rc, t_map map)
{
	rc->side = false;
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

static void	update_player_vectors(t_data *data)
{
	if (data->player.orientation == 'N')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = -1.0;
	}
	else if (data->player.orientation == 'S')
	{
		data->player.dir.x = 0.0;
		data->player.dir.y = 1.0;
	}
	else if (data->player.orientation == 'E')
	{
		data->player.dir.x = 1.0;
		data->player.dir.y = 0.0;
	}
	else if (data->player.orientation == 'W')
	{
		data->player.dir.x = -1.0;
		data->player.dir.y = 0.0;
	}
	data->plane.x = -data->player.dir.y;
	data->plane.y = data->player.dir.x;
}

int	render_frame(void *param)
{
	t_data			*data;
	t_raycast_data	rc;
	size_t			x;
	double			perpwalldist;
	int				line_height;
	t_range			wall_range;

	data = (t_data *)param;
	clear_img(data);
	update_player_vectors(data);
	// Per column Raycasting Pass
	x = 0;
	while (x < (size_t)data->width)
	{
		rc = init_raycast_data(data, x);
		dda_loop(&rc, data->map);

		// After hitting a wall: Compute Wall Metrics
		if (rc.side == false)
			perpwalldist = rc.side_distance.x - rc.delta_distance.x;
		else
			perpwalldist = rc.side_distance.y - rc.delta_distance.y;

		line_height = data->height / perpwalldist;
		wall_range.start = -line_height / 2 + data->height / 2;
		wall_range.end = line_height / 2 + data->height / 2;
		if (wall_range.start >= data->height || wall_range.end < 0)
			return (0);
		if (wall_range.start < 0)
			wall_range.start = 0;
		if (wall_range.end >= data->height)
			wall_range.end = data->height - 1;
		draw_ceiling_floor(data, x, wall_range);
		draw_textured_wall(data, x, wall_range, &rc, perpwalldist, line_height);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img->ptr, 0, 0);
	return (0);
}
