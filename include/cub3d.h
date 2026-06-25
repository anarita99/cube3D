#ifndef CUB3D_H
# define CUB3D_H




typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
}					t_map;

typedef struct s_data
{
	int			fd;
	t_map		map;
}				t_data;

#include "parsing.h"

#endif