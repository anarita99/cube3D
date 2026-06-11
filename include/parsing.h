/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/06/11 14:22:30 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

# define MALL_ERR "Error\n Malloc failed.\n"

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_rgb;
	int		c_rgb;
} t_config;

typedef struct s_game
{
	int		fd;
	char	**map;
	int		map_h;
} t_game;

typedef enum s_types
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	MAP,
	INVALID
} t_types;

//utils.c
int		skip_space(char *line);
char	*find_new_line(char *str);
int		count_words(char *str, char sep);
void	free_things(t_config *config, t_game *game);

void	init_configs(t_config *config, t_game *game);
int		allocate_colour(char *line, t_config *config, t_types type);
char	*extract_config(char *line);

char	**make_map_grid(char *line, int fd, t_game *game);
int		valid_characters(char **map);
int		find_big_line(char **map);
char	**put_map_rect(char **map);
int	is_map_valid(char **map, int height);

#endif