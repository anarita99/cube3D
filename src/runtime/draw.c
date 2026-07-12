/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:53:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/06 15:52:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	draw_ceiling_floor(t_data *data, int x, t_range wall)
{
	t_range	range;

	range.start = 0;
	range.end = wall.start - 1;
	draw_vertical_line(data, x, range, data->assets.ceiling_rgb);
	range.start = wall.end;
	range.end = data->height - 1;
	draw_vertical_line(data, x, range, data->assets.floor_rgb);
}

static double	get_wall_x(t_data *data, t_raycast_data *rc, double perpwalldist)
{
	double	wall_x;

	if (rc->side == false)
		wall_x = data->player.loc.y + perpwalldist * rc->ray_dir.y;
	else
		wall_x = data->player.loc.x + perpwalldist * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	get_texture_x(t_texture texture, double wall_x, t_raycast_data *rc)
{
	int	texture_x;

	texture_x = (int)(wall_x * (double)texture.width);
	if (rc->side == false && rc->ray_dir.x > 0)
		texture_x = texture.width - texture_x - 1;
	if (rc->side == true && rc->ray_dir.y < 0)
		texture_x = texture.width - texture_x - 1;
	return (texture_x);
}

void	draw_textured_wall(t_data *data, int x, t_raycast_data *rc, t_wall_data	wall)
{
	double		wall_x;
	int			texture_x;
	int			texture_y;
	double		step;
	double		texture_pos;
	size_t		y;
	int			color;
	t_texture	texture;
	
	texture = select_wall_texture(data, rc);
	wall_x = get_wall_x(data, rc, wall.perpwalldist);
	texture_x = get_texture_x(texture, wall_x, rc);
	step = 1.0 * (texture.height) / wall.line_height;
	texture_pos = (wall.range.start - data->height / 2 + wall.line_height / 2) * step;

	y = wall.range.start;
	while ((int)y < wall.range.end)
	{
		texture_y = (int)(texture_pos) & (texture.height - 1);
		color = get_texture_color(&texture.img, texture_x, texture_y);
		my_mlx_pixel_put(data->img, x, y, color);
		texture_pos += step;
		y++;
	}
}
