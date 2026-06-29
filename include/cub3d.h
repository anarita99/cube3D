/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/06/29 14:43:37 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// open, close, read, write
# include <unistd.h>
# include <fcntl.h>

// malloc, free, exit
# include <stdlib.h>

// perror + strerror
# include <stdio.h>
# include <string.h>

// INT_MAX, Math, gettimeofday, bool
# include <limits.h>
# include <math.h>
# include <sys/time.h>
# include <stdbool.h>

// MinilibX + X11 + Libft
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// Game Settings
# define GAME_TITLE "Cub3D"
# define PLAYER_FOV 66
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800

// Errors
# define ERR_INVALID_ARG_COUNT 1
# define ERR_EMPTY_FILE 2
# define ERR_INVALID_MAP 3
# define ERR_INVALID_EXT 4
# define ERR_CANT_READ_FILE 5
# define ERR_CANT_INIT_MAP 6
# define ERR_CANT_READ_IMG 7

// Structs

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_vector
{
	double	x;
	double	y;
}			t_vector;

typedef struct s_player
{
	t_vector	loc;
	t_vector	dir;
	char		orientation;
}				t_player;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
}					t_map;

typedef struct s_assets
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_rgb;
	int		ceiling_rgb;
}	t_assets;

typedef struct s_data
{
	int			fd;
	void		*mlx;
	void		*win;
	t_img		*img;
	int			width;
	int			height;
	t_assets	assets;
	t_map		map;
	t_player	player;
	t_vector	plane;
}				t_data;

// Modules
# include "parsing.h"
# include "runtime.h"

// Functions
void	init(t_data *data);
void	cleanup_and_exit(int status_code, const char *error_msg, t_data *data);

#endif