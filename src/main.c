/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adores <adores@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:39:36 by adores            #+#    #+#             */
/*   Updated: 2026/06/26 14:55:43 by adores           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Fake hardcoded map for testing

void	print_config(t_config config, t_map map)
{
	int	i;

	i = 0;
	printf("%s\n", config.no_path);
	printf("%s\n", config.so_path);
	printf("%s\n", config.we_path);
	printf("%s\n", config.ea_path);
	printf("%d\n", config.f_rgb);
	printf("%d\n", config.c_rgb);
	while (map.grid[i])
	{
		printf("%s\n", map.grid[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data		data;

	data.width = WIN_WIDTH;
	data.height = WIN_HEIGHT;

	if (ac != 2)
		return (ft_putstr_fd("Error\n Invalid number of arguments.\n", 2), 1);
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (ft_putstr_fd("Error\n Can't open file.\n", 2), 1);
	init(&data.config, &data.map, &data);
	if (is_file_cub(av[1]) == 0)
	{
		if (read_file(&data, &data.config, &data.map) == 0 && all_configs(data.config) == 0)
		{
			print_config(data.config, data.map);
		}
		close(data.fd);
	}
	else
		return (ft_putstr_fd("Error\n Wrong file.\n", 2), 1);
	
	// Substitui isto pela tua parte
	// Podes simplesmente meter a function acima (get_player_info) no teu codigo
	// E depois apaga a function acima (get_player_info) e o g_world_map
	// --------------------
	
	game(&data);
	free_things(&data.config, &data.map);
	return (0);
}


/*
int	main(int ac, char **av)
{
	t_config	config;
	t_data		data;
	t_map		map;
	
	int			line;

	if (ac != 2)
		return (ft_putstr_fd("Error\n Invalid number of arguments.\n", 2), 1);
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (ft_putstr_fd("Error\n Can't open file.\n", 2), 1);
	init(&config, &map, &data);
	if (is_file_cub(av[1]) == 0)
	{
		if (read_file(&data, &config, &map) == 0 && all_configs(config) == 0)
		{
			print_config(config, map);
			line = find_big_line(map.grid);
			printf("%d\n", line);
		}
		free_things(&config, &data, &map);
	}
	else
		return (ft_putstr_fd("Error\n Wrong file.\n", 2), 1);
	return (0);
}*/