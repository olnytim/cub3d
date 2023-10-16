/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 02:37:22 by olnytim           #+#    #+#             */
/*   Updated: 2023/10/16 18:03:45 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <cub3D.h>

int	ft_hook(int keycode, t_game *game)
{
	printf("keycode: %d\n", keycode);
	printf("\ndir x: %f\ndir y: %f\npos x:%f\npos y: %f\nplane x: %f\nplane y: %f\n", game->player->dir_x, game->player->dir_y,
		game->player->pos_x, game->player->pos_y, game->player->plane_x, game->player->plane_y);
	if (keycode == ESC)
		ft_endgame(game);
	if (keycode == W)
	{
		// game->rays->map_y += 1;			//position
		// game->rays->step_y += 1;
		game->player->pos_y += 1;			//position
		// game->player->dir_y -= 1;		//direction napravleniye
		// if (game->player->plane_x != -0.66)	//vektor
		// 	game->player->plane_x = -0.66;
	}
	if (keycode == S)
	{
		// game->rays->map_y -= 1;
		// game->rays->step_y -= 1;
		game->player->pos_y -= 1;			//position
		// game->player->dir_y += 1;
		// if (game->player->plane_x != 0.66)
		// 	game->player->plane_x = 0.66;
	}
	// if (keycode == D)
	// 	;
	// if (keycode == A)
	// 	;
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_game *game)
{
	(void)game;
//	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	printf("keycode: %d\n", button);
	printf("Mouse position: X = %d, Y = %d\n", x, y);
	return (0);
}
