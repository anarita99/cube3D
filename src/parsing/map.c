/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:59:09 by adores            #+#    #+#             */
/*   Updated: 2026/06/05 15:03:18 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	if(s1 && s2)
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

/*char	**make_map_grid(char *line, int fd)
{
	char	**map;
	char	*tmp;
	int		new_line;

	tmp = NULL;
	new_line = 0;
	tmp = map_line(tmp, line);
	while (1)
	{
		line = get_next_line(fd);	
		if (!line)
			break;
		if (line[0] == '\n')
		{
			new_line = 1;
			free(line);
		}
		else
		{
			if (new_line == 1)
				return (free(tmp), free(line), \
ft_putstr_fd("Error\n New line detected in map.", 2), NULL);
			tmp = map_line(tmp, line);
		}
	}
	map = ft_split(tmp, '\n');
	if (!map)
		return(free(tmp), NULL);
	free(tmp);
	return (map);
}*/

int	check_newline(char	*tmp)
{
	int	i;

	i = 0;
	while(tmp[i])
	{
		if(tmp[i] == '\n' && tmp[i + 1] == '\n')
		{
			while(tmp[i] == '\n')
				i++;
			if (tmp[i] != '\0')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

char	**make_map_grid(char *line, int fd)
{
	char	**map;
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		tmp = map_line(tmp, line);
		line = get_next_line(fd);	
		if (!line)
			break;
	}
	if (check_newline(tmp) == 1)
		return (ft_putstr_fd("Error\n New line detected in map.", 2), \
free(tmp), free(line), NULL);
	map = ft_split(tmp, '\n');
	if (!map)
		return(free(tmp), NULL);
	free(tmp);
	return (map);
}

int	valid_characters(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'W' \
&& map[i][j] != 'E'&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != ' ')
				return (ft_putstr_fd("Error\n Invalid character in map.", 2), 1);
			if (map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'N' || map[i][j] == 'S')
				count++;
			j++;
		}
		i++;
	}
	if (count == 0 || count > 1)
		return(ft_putstr_fd("Error\n The game must have exactly one starting position.", 2), 1);
	return (0);
}
