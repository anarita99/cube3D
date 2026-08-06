/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 15:01:53 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/15 13:36:11 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_wall_tile(t_map map, int x, int y)
{
	if (y < 0 || x < 0 || y >= map.height || x >= map.width)
		return (false);
	if (!map.grid[y] || map.grid[y][x] == '\0')
		return (false);
	return (map.grid[y][x] == '1');
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical_line(t_data *data, int x, t_range range, int color)
{
	int	current_y;

	current_y = range.start;
	while (current_y <= range.end)
	{
		my_mlx_pixel_put(&data->img, x, current_y, color);
		current_y++;
	}
}

int	get_texture_color(t_img tex_img, int x, int y)
{
	char	*color;

	x = x % TEXTURE_RES;
	y = y % TEXTURE_RES;
	color = tex_img.addr + (y * tex_img.line_len + x * (tex_img.bpp / 8));
	return (*(int *)color);
}
