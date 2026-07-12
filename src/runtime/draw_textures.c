/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:53:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/06 15:52:24 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static t_texture	get_front_texture(t_data *data)
{
	if (data->player.orientation == 'N')
		return (data->assets.so);
	else if (data->player.orientation == 'S')
		return (data->assets.no);
	else if (data->player.orientation == 'E')
		return (data->assets.we);
	else
		return (data->assets.ea);
}

static t_texture	get_left_texture(t_data *data)
{
	if (data->player.orientation == 'N')
		return (data->assets.ea);
	else if (data->player.orientation == 'S')
		return (data->assets.we);
	else if (data->player.orientation == 'E')
		return (data->assets.no);
	else
		return (data->assets.so);
}

static t_texture	get_right_texture(t_data *data)
{
	if (data->player.orientation == 'N')
		return (data->assets.we);
	else if (data->player.orientation == 'S')
		return (data->assets.ea);
	else if (data->player.orientation == 'E')
		return (data->assets.so);
	else
		return (data->assets.no);
}

t_texture	select_wall_texture(t_data *data, t_raycast_data *rc)
{
	if (rc->side == true)
		return (get_front_texture(data));
	else if (rc->ray_dir.x <= 0)
		return (get_left_texture(data));
	else
		return (get_right_texture(data));
}
