/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:34 by adores            #+#    #+#             */
/*   Updated: 2026/08/04 11:29:31 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	*split_and_transform_array(char *line)
{
	int		*temp;
	int		i;
	char	**splitted;

	i = -1;
	temp = malloc(sizeof(int) * 3);
	if (!temp)
		return (NULL);
	splitted = ft_split(line, ',');
	if (!splitted)
		return (NULL);
	while (splitted[++i])
	{
		if (is_num(splitted[i]) == 0)
		{
			temp[i] = ft_atoi(splitted[i]);
			if (temp[i] <= 255)
				continue ;
		}
		return (ft_freearray(splitted), free(temp), NULL);
	}
	return (ft_freearray(splitted), temp);
}

static int	rgb_to_int(int r, int g, int b)
{
	int	rgb;

	rgb = (r << 16) | (g << 8) | b;
	return (rgb);
}

// Formula para transformar RGB em int
// return (r << 16) | (g << 8) | b;
static int	get_color_int(char *colour)
{
	int	*colour_code;
	int	rgb_code;

	if (count_words(colour, ',') != 3 || count_commas(colour) != 2)
		return (-1);
	if (count_words(colour, ' ') != 1)
		return (-1);
	else
	{
		colour_code = split_and_transform_array(colour);
		if (!colour_code)
			return (-1);
		rgb_code = rgb_to_int(colour_code[0], colour_code[1], colour_code[2]);
		free(colour_code);
	}
	return (rgb_code);
}

int	assign_color(char *line, t_assets *assets, t_types type)
{
	char	*color_rgb;
	int		color_int;

	color_rgb = ft_strdup(extract_assets(line));
	if (!color_rgb)
		return (1);
	color_int = get_color_int(color_rgb);
	free(color_rgb);
	if (color_int == -1)
		return (1);
	if (type == F && assets->floor_rgb == -1)
		assets->floor_rgb = color_int;
	else if (type == C && assets->ceiling_rgb == -1)
		assets->ceiling_rgb = color_int;
	else
		return (1);
	return (0);
}
