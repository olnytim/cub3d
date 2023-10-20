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

void	ft_camera_move(int keycode, t_game *game, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if (keycode == LEFT || keycode == LEFT_L)
	{
		player->dir_x = player->dir_x * cos(-player->rot_speed)
			- player->dir_y * sin(-player->rot_speed);
		player->dir_y = old_dir_x * sin(-player->rot_speed)
			+ player->dir_y * cos(-player->rot_speed);
		player->plane_x = player->plane_x * cos(-player->rot_speed)
			- player->plane_y * sin(-player->rot_speed);
		player->plane_y = old_plane_x * sin(-player->rot_speed)
			+ player->plane_y * cos(-player->rot_speed);
		ft_raycasting(game);
	}
	if (keycode == RIGHT || keycode == RIGHT_L)
	{
		player->dir_x = player->dir_x * cos(player->rot_speed)
			- player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed)
			+ player->dir_y * cos(player->rot_speed);
		player->plane_x = player->plane_x * cos(player->rot_speed)
			- player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed)
			+ player->plane_y * cos(player->rot_speed);
		ft_raycasting(game);
	}
}

// static void	ft_move(t_game *game, int case)
// {
// 	if (map->map[(int)player->pos_y][(int)(player->pos_x
// 			+ player->dir_x * player->move_speed)] == '0')
// 		player->pos_x += player->dir_x * player->move_speed;
// 	if (map->map[(int)(player->pos_y + player->dir_y
// 			* player->move_speed)][(int)player->pos_x] == '0')
// 		player->pos_y += player->dir_y * player->move_speed;
// 	ft_raycasting(game);
// }

int	ft_hook(int keycode, t_game *game)
{
	t_player	*player;

	player = game->player;
	if (keycode == ESC || keycode == ESC_L)
		ft_endgame(game);
	if (keycode == W || keycode == UP || keycode == W_L || keycode == UP_L)
	{
		if (game->map->map[(int)player->pos_y][(int)(player->pos_x
			+ player->dir_x * player->move_speed)] == '0')
			player->pos_x += player->dir_x * player->move_speed;
		if (game->map->map[(int)(player->pos_y + player->dir_y
				* player->move_speed)][(int)player->pos_x] == '0')
			player->pos_y += player->dir_y * player->move_speed;
		ft_raycasting(game);
	}
	if (keycode == S || keycode == DOWN || keycode == S_L || keycode == DOWN_L)
	{
		if (game->map->map[(int)player->pos_y][(int)(player->pos_x
			+ player->dir_x * player->move_speed)] == '0')
			player->pos_x -= player->dir_x * player->move_speed;
		if (game->map->map[(int)(player->pos_y + player->dir_y
				* player->move_speed)][(int)player->pos_x] == '0')
			player->pos_y -= player->dir_y * player->move_speed;
		ft_raycasting(game);
	}
	if (keycode == A || keycode == A_L)
	{
		if (game->map->map[(int)player->pos_y][(int)(player->pos_x
			+ player->dir_y * player->move_speed)] == '0')
			player->pos_x += player->dir_y * player->move_speed;
		if (game->map->map[(int)(player->pos_y - player->dir_x
				* player->move_speed)][(int)player->pos_x] == '0')
			player->pos_y -= player->dir_x * player->move_speed;
		ft_raycasting(game);
	}
	if (keycode == D || keycode == D_L)
	{
		if (game->map->map[(int)player->pos_y][(int)(player->pos_x
			- player->dir_y * player->move_speed)] == '0')
			player->pos_x -= player->dir_y * player->move_speed;
		if (game->map->map[(int)(player->pos_y + player->dir_x
				* player->move_speed)][(int)player->pos_x] == '0')
			player->pos_y += player->dir_x * player->move_speed;
		ft_raycasting(game);
	}
	ft_camera_move(keycode, game, game->player);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	t_player	*player;

	(void)game;
	(void)y;
	player = game->player;
	mlx_mouse_hide();
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if (x < SCREEN_WIDTH / 2)
	{
		player->dir_x = player->dir_x * cos(-player->rot_speed)
			- player->dir_y * sin(-player->rot_speed);
		player->dir_y = old_dir_x * sin(-player->rot_speed)
			+ player->dir_y * cos(-player->rot_speed);
		player->plane_x = player->plane_x * cos(-player->rot_speed)
			- player->plane_y * sin(-player->rot_speed);
		player->plane_y = old_plane_x * sin(-player->rot_speed)
			+ player->plane_y * cos(-player->rot_speed);
		ft_raycasting(game);
	}
	else
	{
		player->dir_x = player->dir_x * cos(player->rot_speed)
			- player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed)
			+ player->dir_y * cos(player->rot_speed);
		player->plane_x = player->plane_x * cos(player->rot_speed)
			- player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed)
			+ player->plane_y * cos(player->rot_speed);
		ft_raycasting(game);
	}
	printf("keycode: %d\n", button);
	mlx_mouse_move(game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (0);
}
