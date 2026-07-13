/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:59:20 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/13 15:32:11 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

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

static t_wall_data	compute_wall_draw(t_data *data, t_raycast_data *rc)
{
	t_wall_data	wall;

	if (rc->side == false)
		wall.perpwalldist = rc->side_distance.x - rc->delta_distance.x;
	else
		wall.perpwalldist = rc->side_distance.y - rc->delta_distance.y;
	wall.line_height = data->height / wall.perpwalldist;
	wall.range.start = -wall.line_height / 2 + data->height / 2;
	wall.range.end = wall.line_height / 2 + data->height / 2;
	if (wall.range.start >= data->height || wall.range.end < 0)
		return (wall);
	if (wall.range.start < 0)
		wall.range.start = 0;
	if (wall.range.end >= data->height)
		wall.range.end = data->height - 1;
	return (wall);
}

static void	render_column(t_data *data, size_t x)
{
	t_raycast_data	rc;
	t_wall_data		wall;

	rc = init_raycast_data(data, x);
	dda_loop(&rc, data->map);
	wall = compute_wall_draw(data, &rc);
	draw_ceiling_floor(data, x, wall.range);
	draw_textured_wall(data, x, &rc, wall);
}

int	render_frame(void *param)
{
	t_data			*data;
	size_t			x;

	data = (t_data *)param;
	clear_img(data);
	update_player_vectors(data);
	x = 0;
	while (x < (size_t)data->width)
	{
		render_column(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	return (0);
}
