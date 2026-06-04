/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:42:08 by leramos-          #+#    #+#             */
/*   Updated: 2026/06/03 13:09:58 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
}

static int	render(void *param)
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

int	main(void)
{
	t_data	data;
	t_img	img;

	data.width = WIN_WIDTH;
	data.height = WIN_HEIGHT;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, data.width, data.height, GAME_TITLE);

	data.img = &img;
	data.img->img = mlx_new_image(data.mlx, data.width, data.height);
	data.img->addr = mlx_get_data_addr(data.img->img, &data.img->bits_per_pixel, &data.img->line_len, &data.img->endian);

	my_mlx_pixel_put(data.img, 4, 4, 0x00FF0000);
	mlx_put_image_to_window(data.mlx, data.win, data.img->img, 0, 0);

	mlx_hook(data.win, DESTROY_EVENT, NO_MASK, destroy_handler, &data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
}
