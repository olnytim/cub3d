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

void	ft_camera_move(int keycode, t_game *game)
{
	double	old_dir_x = game->player->dir_x;
	double	old_plane_x = game->player->plane_x;

	if (keycode == LEFT || keycode == LEFT_L)
	{
		game->player->dir_x = game->player->dir_x * cos(-game->player->rot_speed)
							- game->player->dir_y * sin(-game->player->rot_speed);
		game->player->dir_y = old_dir_x * sin(-game->player->rot_speed)
							+ game->player->dir_y * cos(-game->player->rot_speed);

		game->player->plane_x = game->player->plane_x * cos(-game->player->rot_speed)
							- game->player->plane_y * sin(-game->player->rot_speed);
		game->player->plane_y = old_plane_x * sin(-game->player->rot_speed)
							+ game->player->plane_y * cos(-game->player->rot_speed);
		ft_raycasting(game);
	}
	if (keycode == RIGHT || keycode == RIGHT_L)
	{
		game->player->dir_x = game->player->dir_x * cos(game->player->rot_speed)
				- game->player->dir_y * sin(game->player->rot_speed);
		game->player->dir_y = old_dir_x * sin(game->player->rot_speed)
				+ game->player->dir_y * cos(game->player->rot_speed);

		game->player->plane_x = game->player->plane_x * cos(game->player->rot_speed)
				- game->player->plane_y * sin(game->player->rot_speed);
		game->player->plane_y = old_plane_x * sin(game->player->rot_speed)
				+ game->player->plane_y * cos(game->player->rot_speed);
		ft_raycasting(game);
	}
}

// static void	ft_move(t_game *game, int case)
// {
// 	if (game->map->map[(int)game->player->pos_y][(int)(game->player->pos_x
// 			+ game->player->dir_x * game->player->move_speed)] == '0')
// 		game->player->pos_x += game->player->dir_x * game->player->move_speed;
// 	if (game->map->map[(int)(game->player->pos_y + game->player->dir_y
// 			* game->player->move_speed)][(int)game->player->pos_x] == '0')
// 		game->player->pos_y += game->player->dir_y * game->player->move_speed;
// 	ft_raycasting(game);
// }

int	ft_hook(int keycode, t_game *game)
{
	printf("keycode: %d\n", keycode);
	if (keycode == ESC || keycode == ESC_L)
		ft_endgame(game);
	if (keycode == W || keycode == UP || keycode == W_L || keycode == UP_L)
	{
		if (game->map->map[(int)game->player->pos_y][(int)(game->player->pos_x
				+ game->player->dir_x * game->player->move_speed)] == '0')
			game->player->pos_x += game->player->dir_x * game->player->move_speed;
		if (game->map->map[(int)(game->player->pos_y + game->player->dir_y
				* game->player->move_speed)][(int)game->player->pos_x] == '0')
			game->player->pos_y += game->player->dir_y * game->player->move_speed;
		ft_raycasting(game);
	}
	if (keycode == S || keycode == DOWN || keycode == S_L || keycode == DOWN_L)
	{
		if (game->map->map[(int)game->player->pos_y][(int)(game->player->pos_x
				+ game->player->dir_x * game->player->move_speed)] == '0')
			game->player->pos_x -= game->player->dir_x * game->player->move_speed;
		if (game->map->map[(int)(game->player->pos_y + game->player->dir_y
				* game->player->move_speed)][(int)game->player->pos_x] == '0')
			game->player->pos_y -= game->player->dir_y * game->player->move_speed;
		ft_raycasting(game);
	}
	if (keycode == A || keycode == A_L)
	{
		if (game->map->map[(int)game->player->pos_y][(int)(game->player->pos_x
				+ game->player->dir_y * game->player->move_speed)] == '0')
			game->player->pos_x += game->player->dir_y * game->player->move_speed;
		if (game->map->map[(int)(game->player->pos_y - game->player->dir_x
				* game->player->move_speed)][(int)game->player->pos_x] == '0')
			game->player->pos_y -= game->player->dir_x * game->player->move_speed;
		ft_raycasting(game);
	}
	if (keycode == D || keycode == D_L)
	{
		if (game->map->map[(int)game->player->pos_y][(int)(game->player->pos_x
				- game->player->dir_y * game->player->move_speed)] == '0')
			game->player->pos_x -= game->player->dir_y * game->player->move_speed;
		if (game->map->map[(int)(game->player->pos_y + game->player->dir_x
				* game->player->move_speed)][(int)game->player->pos_x] == '0')
			game->player->pos_y += game->player->dir_x * game->player->move_speed;
		ft_raycasting(game);
	}
	ft_camera_move(keycode, game);
	return (0);
}

int	ft_mouse_hook(int button, t_game *game)
{
// 	int	*x;
// 	int	*y;

// 	x = NULL;
// 	y = NULL;
	(void)game;
	// mlx_mouse_hide();
	printf("hi\n");
	// mlx_mouse_get_pos(game->win, x, y);
	printf("hi\n");
	// printf("x and y: %d, %d\n", *x, *y);
	printf("keycode: %d\n", button);
	// printf("Mouse position: X = %d, Y = %d\n", x, y);
	return (0);
}
