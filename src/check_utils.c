/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:22:58 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/19 16:43:38 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

char	*ft_skip_spaces(char *line)
{
	while (*line == ' ')
		++line;
	return (line);
}

void	ft_empty(char *line)
{
	if (!*line)
		ft_exit("File is empty");
}

int	ft_check_path_color(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (0);
		++line;
	}
	return (1);
}

static void	check_position(char pos, char player)
{
	if (pos != '1' && pos != '0' && pos != player)
		ft_exit("Wrong fill of map");
}

void	ft_check_fence(t_game *game, int x, int y)
{
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == game->map->dir)
			{
				game->player->pos_x = x;
				game->player->pos_y = y;
				game->map->map[y][x] = '0';
			}
			if (game->map->map[y][x] == '0')
			{
				if (y == 0 || y == game->map->map_size)
					ft_exit("There is no walls in first or last line\n");
				check_position(game->map->map[y + 1][x], game->map->dir);
				check_position(game->map->map[y - 1][x], game->map->dir);
				check_position(game->map->map[y][x + 1], game->map->dir);
				check_position(game->map->map[y][x - 1], game->map->dir);
			}
			++x;
		}
		++y;
	}
}
