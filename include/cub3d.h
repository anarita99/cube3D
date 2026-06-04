/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/06/02 14:08:37 by leramos-         ###   ########.fr       */
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

// INT_MAX, Math, gettimeofday
# include <limits.h>
# include <math.h>
# include <sys/time.h>

// MinilibX + Libft
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

// Game Settings
# define GAME_TITLE "Cub3D"
# define PLAYER_FOV 66
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Errors
# define ERR_INVALID_ARG_COUNT 1
# define ERR_EMPTY_FILE 2
# define ERR_INVALID_MAP 3
# define ERR_INVALID_EXT 4
# define ERR_CANT_READ_FILE 5
# define ERR_CANT_INIT_MAP 6
# define ERR_CANT_READ_IMG 7

// Events & Masks
# define DESTROY_EVENT 17
# define NO_MASK 0L

// Key Values
# define K_ESC 65307
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100

// Structs

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		*img;
	int			width;
	int			height;
}				t_data;

// Render
int		draw_elements(void *param);

// Events
int		destroy_handler(void *param);

// Exit
void	cleanup_and_exit(int status_code, const char *error_msg, t_data *data);

#endif