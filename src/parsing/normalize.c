/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 11:21:55 by adores            #+#    #+#             */
/*   Updated: 2026/06/08 14:58:11 by adores           ###   ########.fr       */
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
	while(map[i])
	{
		j = 0;
		while(map[i][j])
			j++;
		if (j > tmp)
			tmp = j;
		i++;
	}
	return(tmp);
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
				return(NULL);
			ft_memset(map_line, ' ', size);
			map_line[size] = '\0';
			ft_memcpy(map_line, map[i], j);
			free(map[i]);
			map[i] = map_line;
		}
	}
	return (map);
}
