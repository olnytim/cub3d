#include "../include/cub3D.h"
#include <cub3D.h>

void	ft_free_matrix(char **str)
{
	int	x;

	x = 0;
	while (str && str[x])
		free(str[x++]);
	free(str);
}
