/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:59:09 by adores            #+#    #+#             */
/*   Updated: 2026/07/15 15:14:09 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*map_line(char *s1, char *s2)
{
	size_t	buffer_size;
	char	*dst;

	if (!s1)
		buffer_size = ft_strlen(s2) + 1;
	else
		buffer_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(buffer_size);
	if (!dst)
		return (NULL);
	if (s1 && s2)
	{
		ft_strlcpy(dst, s1, buffer_size);
		ft_strlcat(dst, s2, buffer_size);
	}
	else
		ft_strlcpy(dst, s2, buffer_size);
	free(s1);
	free(s2);
	return (dst);
}

int	check_newline(char	*tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\n' && (tmp[i + 1] == '\n' || tmp[i + 1] == ' '))
		{
			while (tmp[i] == '\n' || tmp[i] == ' ')
				i++;
			if (tmp[i] != '\0')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

char	**make_map_grid(char *line, int fd, t_map *map)
{
	char	**grid;
	char	*tmp;
	int		count;

	tmp = NULL;
	count = 0;
	while (1)
	{
		tmp = map_line(tmp, line);
		line = get_next_line(fd);
		count++;
		if (!line)
			break ;
	}
	if (check_newline(tmp) == 1)
		return (ft_putstr_fd("Error\n New line detected in map.\n", 2), \
free(tmp), free(line), NULL);
	grid = ft_split(tmp, '\n');
	if (!grid)
		return (free(tmp), NULL);
	free(tmp);
	map->height = count;
	return (grid);
}

static int	valid_row(char **map, t_data *data, int i)
{
	int	j;

	j = -1;
	while (map[i][++j])
	{
		if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == ' ')
			continue ;
		if (map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'N' \
|| map[i][j] == 'S')
		{
			if (data->player.orientation == '\0')
			{
				data->player.loc.y = i;
				data->player.loc.x = j;
				data->player.orientation = map[i][j];
				continue ;
			}
			else
				return (ft_putstr_fd(PL_POS, 2), 1);
		}
		return (ft_putstr_fd("Error\n Invalid character.\n", 2), 1);
	}
	return (0);
}

int	valid_characters(char **map, t_data *data)
{
	int	i;

	i = -1;
	while (map[++i])
	{
		if (valid_row(map, data, i))
			return (1);
	}
	if (data->player.orientation == '\0')
		return (ft_putstr_fd(PL_POS, 2), 1);
	return (0);
}
