/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:42:08 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/06 15:09:06 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

// Todo
//
// change var names
// norminette
// leaks
// norminette again

void	game(t_data *data)
{
	t_img	img;

	init_mlx_window(data);
	init_render_image(data, &img);
	load_textures(data);

	mlx_hook(data->win, DestroyNotify, NoEventMask, destroy_handler, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handler, data);
	mlx_loop_hook(data->mlx, render_frame, data);
	mlx_loop(data->mlx);
}
