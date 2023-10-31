/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lykostan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:27:41 by lykostan          #+#    #+#             */
/*   Updated: 2023/10/31 17:27:57 by lykostan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	split_size(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		;
	return (i);
}

void	minimap(t_game *game, int i, int j)
{
	int	x;
	int	y;

	x = (int)game->player->pos_x;
	y = (int)game->player->pos_y;
	while (++i < 150)
	{
		j = 4;
		while (++j < 150)
		{
			if (i / 10 == 7 && j / 10 == 7)
				mlx_pixel_put(game->mlx, game->win, j, i, 0x050FFFFFF);
			else if (y - 7 + i / 10 > -1 && y - 7 + i / 10
				< split_size(game->map->map) && x - 7 + j / 10 > -1
				&& x - 7 + j / 10 < (int)ft_strlen(game->map->map[y
						- 7 + i / 10]))
			{
				if (game->map->map[y - 7 + i / 10][x - 7 + j / 10] == 48)
					mlx_pixel_put(game->mlx, game->win, j, i, 0x050808080);
				else if (game->map->map[y - 7 + i / 10][x - 7 + j / 10] == 49)
					mlx_pixel_put(game->mlx, game->win, j, i, 0x050000060);
			}
		}
	}
}
