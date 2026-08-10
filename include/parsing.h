/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/07/13 16:08:43 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <common.h>

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
}	t_types;

// Utils
int		skip_space(char *line);
char	*find_new_line(char *str);
int		count_words(char *str, char sep);

// File Utils
bool	is_file_cub(char *filename);
t_types	find_type(char *line);
char	*extract_assets(char *line);

// File Validation
bool	is_map_file_valid(t_data *data);
int		count_commas(char *s);
int		allocate_colour(char *line, t_assets *assets, t_types type);
char	**make_map_grid(char *line, int fd, t_map *map);
bool	valid_characters(char **map, t_data *data);
int		find_big_line(char **map);
int		put_map_rect(t_map *map);
bool	is_map_valid(t_map map);

#endif