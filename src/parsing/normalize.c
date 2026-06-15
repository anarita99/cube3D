/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:21:55 by adores            #+#    #+#             */
/*   Updated: 2026/06/15 14:02:20 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_big_line(char **map)
{
	int	tmp;
	int	i;
	int	j;

	tmp = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > tmp)
			tmp = j;
		i++;
	}
	return (tmp);
}

char	**put_map_rect(char **map)
{
	int		i;
	int		j;
	int		size;
	char	*map_line;

	size = find_big_line(map);
	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != size)
		{
			map_line = malloc(sizeof(char) * (size + 1));
			if (!map_line)
				return (ft_putstr_fd(MALL_ERR, 2), NULL);
			ft_memset(map_line, ' ', size);
			map_line[size] = '\0';
			ft_memcpy(map_line, map[i], j);
			free(map[i]);
			map[i] = map_line;
		}
	}
	return (map);
}

int	is_char(char **map, int i, int j, char c)
{
	if (map[i][j + 1] == c || map[i][j - 1] == c \
|| map[i + 1][j] == c || map[i - 1][j] == c)
		return (1);
	return (0);
}

static int	check_errors(char **map, int i, int j, int height)
{
	if (j == 0 && (map[i][j] != '1' && map[i][j] != ' '))
		return (ft_putstr_fd("Error\n Invalid map2.\n", 2), 1);
	if (i == 0 || i == height)
	{
		if (map[i][j] != '1' && map[i][j] != ' ' )
			return (ft_putstr_fd("Error\n Invalid map1.\n", 2), 1);
	}
	if (map[i][j] == '0')
	{
		if (is_char(map, i, j, ' ') == 1)
			return (ft_putstr_fd("Error\n Invalid map2.\n", 2), 1);
	}
	if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N' \
|| map[i][j] == 'S')
	{
		if (is_char(map, i, j, ' ') == 1)
			return (ft_putstr_fd("Error\n Invalid map3.\n", 2), 1);
	}
	return (0);
}

int	is_map_valid(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (check_errors(map, i, j, height) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*int	is_map_valid(char **map, int height)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (j == 0 && (map[i][j] != '1' && map[i][j] != ' '))
					return (ft_putstr_fd("Error\n Invalid map2.\n", 2), 1);
			if (i == 0 || i == height)
			{
				if (map[i][j] != '1' && map[i][j] != ' ' )
					return (ft_putstr_fd("Error\n Invalid map1.\n", 2), 1);
			}
			if (map[i][j] == '0')
			{
				if (is_char(map, i, j, ' ') == 1)
					return (ft_putstr_fd("Error\n Invalid map2.\n", 2), 1);
			}
			if (map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'S')
			{
				if (is_char(map, i, j, ' ') == 1)
					return (ft_putstr_fd("Error\n Invalid map3.\n", 2), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}*/
