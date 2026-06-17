/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 12:16:34 by adores            #+#    #+#             */
/*   Updated: 2026/06/17 15:20:17 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_num(char *str)
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

int	*split_and_transform_array(char *line)
{
	int		*temp;
	int		i;
	char	**splitted;

	i = -1;
	temp = malloc(sizeof(int) * 3);
	if (!temp)
		return (ft_putstr_fd(MALL_ERR, 2), NULL);
	splitted = ft_split(line, ',');
	if (!splitted)
		return (ft_putstr_fd(MALL_ERR, 2), NULL);
	while (splitted[++i])
	{
		if (is_num(splitted[i]) == 0)
		{
			temp[i] = ft_atoi(splitted[i]);
			if (temp[i] < 255)
				continue ;
		}
		ft_putstr_fd("Error\n Wrong colour code.\n", 2);
		return (ft_freearray(splitted), free(temp), NULL);
	}
	return (ft_freearray(splitted), temp);
}

int	rgb_to_int(int r, int g, int b)
{
	int	rgb;

	rgb = (r << 16) | (g << 8) | b;
	return (rgb);
}

//formula pra transformar rgb em int
// return (r << 16) | (g << 8) | b;
int	get_colour_int(char *colour)
{
	int	*colour_code;
	int	rgb_code;

	if (count_words(colour, ',') != 3 || count_commas(colour) != 2)
		return (ft_putstr_fd("Error\n Wrong colour code.\n", 2), -1);
	if (count_words(colour, ' ') != 1)
	{
		ft_putstr_fd("Error\n Too many words for a colour code.\n", 2);
		return (-1);
	}
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

int	allocate_colour(char *line, t_config *config, t_types type)
{
	char	*colour;
	int		colour_code;

	colour = ft_strdup(extract_config(line));
	if (!colour)
		return (ft_putstr_fd("Error\n Malloc error.\n", 2), 1);
	colour_code = get_colour_int(colour);
	free(colour);
	if (colour_code == -1)
		return (1);
	if (type == F && config->f_rgb == -1)
		config->f_rgb = colour_code;
	else if (type == C && config->c_rgb == -1)
		config->c_rgb = colour_code;
	else
		return (ft_putstr_fd("Error\n Double colour detected.\n", 2), 1);
	return (0);
}
