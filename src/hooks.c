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
//	printf("\ndir x: %f\ndir y: %f\npos x:%f\npos y: %f\nplane x: %f\nplane y: %f\n", game->player->dir_x, game->player->dir_y,
//		game->player->pos_x, game->player->pos_y, game->player->plane_x, game->player->plane_y);
	if (keycode == ESC)
		ft_endgame(game);
	if (keycode == W)
	{
		game->player->pos_y -= 1;
		if (game->player->dir_y == 1)
			game->player->pos_y += 2;
		ft_raycasting(game);
	}
	if (keycode == S)
	{
		game->player->pos_y -= 1;
		if (game->player->dir_y == -1)
			game->player->pos_y += 2;
		ft_raycasting(game);
	}
	if (keycode == D)
	{
		game->player->pos_x += 1;
		ft_raycasting(game);
	}
	if (keycode == A)
	{
		game->player->pos_x -= 1;
		ft_raycasting(game);
	}
	if (keycode == LEFT)
		;
	if (keycode == RIGHT)
		;
	if (keycode == UP)
	{
		game->player->pos_y -= 1;
		if (game->player->dir_y == -1)
			game->player->pos_y += 2;
		ft_raycasting(game);
	}
	if (keycode == DOWN)
	{
		game->player->pos_y -= 1;
		if (game->player->dir_y == 1)
			game->player->pos_y += 2;
		ft_raycasting(game);
	}
	return (0);
}

int	ft_mouse_hook(int button, t_game *game)
{
	int	*x;
	int	*y;

	x = NULL;
	y = NULL;
	mlx_mouse_hide();
	printf("hi\n");
	mlx_mouse_get_pos(game->win, x, y);
	printf("hi\n");
	printf("x and y: %d, %d\n", *x, *y);
	printf("keycode: %d\n", button);
	// printf("Mouse position: X = %d, Y = %d\n", x, y);
	return (0);
}
