/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:33:42 by adores            #+#    #+#             */
/*   Updated: 2026/06/01 12:04:09 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>

# define MALL_ERR "Error: Malloc failed.\n"

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_rgb;
	int		c_rgb;
} t_config;

typedef enum s_types
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	INVALID
} t_types;

//utils.c
int		skip_space(char *line);
char	*find_new_line(char *str);
void	free_paths(t_config *config);

void	init_configs(t_config *config);
int		allocate_colour(char *line, t_config *config, t_types type);
char	*extract_config(char *line);

#endif