/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:25:13 by adores            #+#    #+#             */
/*   Updated: 2026/05/25 15:09:37 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_file_cub(char *filename)
{
	int		i;
	char	*cub;

	cub = ".cub";
	i = 0;
	while (filename[i])
		i++;
	if (ft_strncmp(&filename[i - 4], cub, 5) == 0)
		return (0);
	return (1);
}

int	skip_space(char *line)
{
	int i;

	i = 0;
	while(line[i] == ' ')
			i++;
	return (i);
}

void	find_path(char *line, char *texture)
{
	int i = 0;
	i = skip_space(line);
	if ((ft_strncmp(&line[i], texture, 2) == 0) && line[i + 2] == ' ')
	{
		i += 2;
		i += skip_space(&line[i]);
		printf("%s", &line[i]);
	}
}

void	find_colours(char *line, char *configs)
{
	int i = 0;
	i = skip_space(line);
	if ((ft_strncmp(&line[i], configs, 1) == 0) && line[i + 1] == ' ')
	{
		i += 2;
		i += skip_space(&line[i]);
		printf("%s", &line[i]);
	}
}

int read_map(char *filename)
{
	char	*line;
	int		fd;
	//int i;
	//t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while((line = get_next_line(fd)))
	{
		find_path(line, "NO");
		find_path(line, "SO");
		find_path(line, "WE");
		find_path(line, "EA");
		find_colours(line, "F");
		find_colours(line, "C");
		free(line);
	}
	close(fd);	
	return (0);
}

int main()
{
	char *filename = "maps/map.cub";
	if(is_file_cub(filename) == 0)
		read_map(filename);
}