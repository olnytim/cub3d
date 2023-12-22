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
#include "../include/cub3D.h"

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

int	animation(t_game *game)
{
	static int	stat;
	void		*img_left;
	void		*img_right;
	int			img_w;
	int			img_h;

	img_left = mlx_xpm_file_to_image(game->mlx, HAND_L, &img_w, &img_h);
	img_right = mlx_xpm_file_to_image(game->mlx, HAND_R, &img_w, &img_h);
	if (!img_left && !img_right)
		ft_exit(IMG_ERR);
//	if (stat < 30)
//	{
//		if (stat < 15)
//			mlx_put_image_to_window(game->mlx, game->win, img,
//				SCREEN_WIDTH / 3 - img_w, 3 * SCREEN_HEIGHT / 4 - img_h);
//		else
//			mlx_put_image_to_window(game->mlx, game->win, img,
//				SCREEN_WIDTH / 3 - img_w, 4 * SCREEN_HEIGHT / 5 - img_h);
//		stat++;
//	}
//	else
//		stat = 0;
//	ft_raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, img_left,
		SCREEN_WIDTH / 3 - img_w, SCREEN_HEIGHT * 3 / 4 - img_h + stat);
	mlx_put_image_to_window(game->mlx, game->win, img_right,
		SCREEN_WIDTH * 2 / 3 - img_w, SCREEN_HEIGHT * 3 / 4 - img_h + stat);

	mlx_destroy_image(game->mlx, img_left);
	mlx_destroy_image(game->mlx, img_right);
	return (0);
}
