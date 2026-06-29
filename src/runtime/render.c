/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 14:59:20 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/29 14:38:06 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	draw_vertical_line(t_data *data, int x, int top, int bottom, int color)
{
	int	current_y;

	current_y = top;
	while (current_y <= bottom)
	{
		my_mlx_pixel_put(data->img, x, current_y, color);
		current_y++;
	}
}

static void	clear_img(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			my_mlx_pixel_put(data->img, x, y, 0x00000000);
			y++;
		}
		x++;
	}
}

int	render(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	data = (t_data *)param;
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			my_mlx_pixel_put(data->img, x, y, 0x00008B);
			x++;
		}
		y++;
	}
	my_mlx_pixel_put(data->img, 4, 4, 0x00FF0000);
	draw_vertical_line(data, 5, 0, 60, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	return (0);
}

static t_raycast_data	init_raycast_data(t_data *data, size_t current_x)
{
	t_raycast_data	rc;
	double			camera_x;
	t_vector		ray_dir;

	camera_x = 2.0 * current_x / data->width - 1.0;
	ray_dir.x = data->player.dir.x + data->plane.x * camera_x;
	ray_dir.y = data->player.dir.y + data->plane.y * camera_x;
	rc.delta_distance.x = fabs(1.0 / ray_dir.x);
	rc.delta_distance.y = fabs(1.0 / ray_dir.y);
	rc.map.x = (int)data->player.loc.x;
	rc.map.y = (int)data->player.loc.y;
	if (ray_dir.x < 0)
	{
		rc.step.x = -1;
		rc.side_distance.x = (data->player.loc.x - rc.map.x) * rc.delta_distance.x;
	}
	else
	{
		rc.step.x = 1;
		rc.side_distance.x = (rc.map.x + 1.0 - data->player.loc.x) * rc.delta_distance.x;
	}

	if (ray_dir.y < 0)
	{
		rc.step.y = -1;
		rc.side_distance.y = (data->player.loc.y - rc.map.y) * rc.delta_distance.y;
	}
	else
	{
		rc.step.y = 1;
		rc.side_distance.y = (rc.map.y + 1.0 - data->player.loc.y) * rc.delta_distance.y;
	}
	return (rc);
}

static int	dda_loop(t_raycast_data *rc, t_map map)
{
	int		side;

	while (true)
	{
		// Jump to next map square, either in x-direction, or in y-direction
		if (rc->side_distance.x < rc->side_distance.y)
		{
			rc->side_distance.x += rc->delta_distance.x;
			rc->map.x += rc->step.x;
			side = 0;
		}
		else
		{
			rc->side_distance.y += rc->delta_distance.y;
			rc->map.y += rc->step.y;
			side = 1;
		}

		// Check if ray has hit a wall
		if (is_wall_tile(map, (int)rc->map.x, (int)rc->map.y))
			break;
	}
	return (side);
}

static void	draw_image(t_data *data, size_t x, int wall_start, int wall_end)
{
	if (wall_start > 0)
		draw_vertical_line(data, x, 0, wall_start - 1, data->assets.ceiling_rgb);
	draw_vertical_line(data, x, wall_start, wall_end, 0x00FF0000);
	if (wall_end < data->height - 1)
		draw_vertical_line(data, x, wall_end + 1, data->height - 1, data->assets.floor_rgb);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

int	render_frame(void *param)
{
	t_data			*data;
	t_raycast_data	rc;
	size_t	x;
	int		side;
	double	perpwalldist;
	int		line_height;
	int		draw_start;
	int		draw_end;

	data = (t_data *)param;
	clear_img(data);
	// Per column Raycasting Pass
	x = 0;
	while (x < (size_t)data->width)
	{
		rc = init_raycast_data(data, x);
		side = dda_loop(&rc, data->map);

		// After hitting a wall
		if (side == 0)
			perpwalldist = rc.side_distance.x - rc.delta_distance.x;
		else
			perpwalldist = rc.side_distance.y - rc.delta_distance.y;
		
		line_height = data->height / perpwalldist;
		draw_start = -line_height / 2 + data->height / 2;
		draw_end = line_height / 2 + data->height / 2;
		
		if (draw_start >= data->height || draw_end < 0)
			return (0);
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= data->height)
			draw_end = data->height - 1;

		draw_image(data, x, draw_start, draw_end);

		x++;
	}
	return (0);
}
