/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 11:39:36 by adores            #+#    #+#             */
/*   Updated: 2026/06/29 14:43:50 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_assets(t_assets assets, t_map map)
{
	int	i;

	i = 0;
	printf("%s\n", assets.no_path);
	printf("%s\n", assets.so_path);
	printf("%s\n", assets.we_path);
	printf("%s\n", assets.ea_path);
	printf("%d\n", assets.floor_rgb);
	printf("%d\n", assets.ceiling_rgb);
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
	init(&data);
	data.fd = open(av[1], O_RDONLY);
	if (data.fd < 0)
		return (ft_putstr_fd("Error\n Can't open file.\n", 2), 1);
	if (is_file_cub(av[1]) == 0)
	{
		if (read_file(&data, &data.assets, &data.map) == 0 && all_assets(data.assets) == 0)
		{
			print_assets(data.assets, data.map);
		}
		close(data.fd);
	}
	else
		return (ft_putstr_fd("Error\n Wrong file.\n", 2), 1);
	game(&data);
	free_things(&data.assets, &data.map);
	return (0);
}
