/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:53:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/06 15:52:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_vertical_line(t_data *data, int x, int top, int bottom, int color)
{
	int	current_y;

	current_y = top;
	while (current_y <= bottom)
	{
		my_mlx_pixel_put(data->img, x, current_y, color);
		current_y++;
	}
}

void	clear_img(t_data *data)
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
