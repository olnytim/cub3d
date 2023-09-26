/* ************************************************************************** */
/*                                                                            */
/*                                                    *._           _.*   @   */
/*   check_colors.c                                     |\  \\_//  /|     #   */
/*                                                      \/         \/     $   */
/*   By: olnytim <yearagotomorrow@gmail.com>           _|_    V  V  |_    %   */
/*                                                  *=.    =  _*  =   .=* ^   */
/*   Created: 2023/09/26 18:24:01 by olnytim           \= ___________=/   &   */
/*   Updated: 2023/09/26 18:24:02 by olnytim                /     \       *   */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

static void	ft_trim_spaces(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		arr[i] = ft_strtrim(arr[i], " ");
		++i;
	}
}

static int	ft_number(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '0' && ft_strlen(num) != 1)
		ft_exit("number starts with 0\n");
	else if (num[0] == '0' && ft_strlen(num) == 1)
		return (i);
	while (num[i])
	{
		if (!(num[i] >= '0' && num[i] <= '9'))
			ft_exit("Invalid character in color");
		++i;
	}
	i = ft_atoi(num);
	if (!(i >= 0 && i <= 255))
		ft_exit("RBG color should be from 0 to 255\n");
	return (i);
}

static void	ft_fill_arr(char **arr, int *color)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (i >= 3)
			ft_exit("Input valid number of color for RGB\n");
		color[i] = ft_number(arr[i]);
		free(arr[i]);
		++i;
	}
	free(arr);
}

void	ft_convert_colors(t_game *game)
{
	int		*ceiling_color;
	int		*floor_color;
	char	**f_color;
	char	**c_color;

	f_color = ft_split(game->map->f_color, ',');
	c_color = ft_split(game->map->c_color, ',');
	ft_trim_spaces(f_color);
	ft_trim_spaces(c_color);
	ceiling_color = malloc(sizeof(int) * 4);
	malloc_err(*ceiling_color, "ceiling color");
	floor_color = malloc(sizeof(int) * 4);
	malloc_err(*floor_color, "floor color");
	ceiling_color[3] = -1;
	floor_color[3] = -1;
	ft_fill_arr(f_color, floor_color);
	ft_fill_arr(c_color, ceiling_color);
	game->ceiling_color = (ceiling_color[0] << 16)
		| (ceiling_color[1] << 8) | ceiling_color[2];
	game->floor_color = (floor_color[0] << 16)
		| (floor_color[1] << 8) | floor_color[2];
}