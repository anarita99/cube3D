/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/06/24 16:16:19 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include <cub3d.h>

typedef struct s_raycast_data
{
	t_vector	delta_distance;
	t_vector	side_distance;
	t_vector	step;
	t_vector	map;
}				t_raycast_data;

// Utils
bool	is_wall_tile(t_map map, int x, int y);

// Render
int		render_frame(void *param);

// Events
int		key_handler(int keycode, void *param);
int		destroy_handler(void *param);

// Main
void	game(t_data *data);

#endif