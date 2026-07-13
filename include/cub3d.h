/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/07/13 16:10:01 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// Game Settings
# define GAME_TITLE "Cub3D"
# define PLAYER_FOV 66
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define TEXTURE_RES 64

// Errors
# define ERR_INVALID_ARG_COUNT 1
# define ERR_EMPTY_FILE 2
# define ERR_INVALID_MAP 3
# define ERR_INVALID_EXT 4
# define ERR_CANT_READ_FILE 5
# define ERR_CANT_INIT_MAP 6
# define ERR_CANT_READ_IMG 7

// // Modules
# include "parsing.h"
# include "runtime.h"

// Functions
void	init(t_data *data);
void	cleanup_and_exit(int status_code, const char *error_msg, t_data *data);

#endif