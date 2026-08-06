/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:59:20 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/27 14:35:39 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static t_wall_data	compute_wall_draw(t_data *data, t_raycast *rc)
{
	t_wall_data	wall;

	if (rc->side == false)
		wall.perpwalldist = rc->side_distance.x - rc->delta_distance.x;
	else
		wall.perpwalldist = rc->side_distance.y - rc->delta_distance.y;
	if (wall.perpwalldist < 0.05)
		wall.perpwalldist = 0.05;
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
	t_raycast	rc;
	t_wall_data	wall;

	rc = init_raycast_data(data, x);
	dda_loop(&rc, data->map);
	wall = compute_wall_draw(data, &rc);
	draw_ceiling_floor(data, x, wall.range);
	draw_textured_wall(data, x, &rc, wall);
}

void	render_frame(t_data *data)
{
	size_t	x;

	clear_img(data);
	x = 0;
	while (x < (size_t)data->width)
	{
		render_column(data, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}
