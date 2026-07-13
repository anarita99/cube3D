/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leramos- <leramos-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:53:44 by leramos-          #+#    #+#             */
/*   Updated: 2026/07/13 14:38:04 by leramos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

int	get_orientation_index(char orientation)
{
	if (orientation == 'N')
		return (0);
	if (orientation == 'E')
		return (1);
	if (orientation == 'S')
		return (2);
	else
		return (3);
}

char	get_orientation_at(int index)
{
	static const char	orientations[4] = {'N', 'E', 'S', 'W'};

	return (orientations[(index % 4 + 4) % 4]);
}
