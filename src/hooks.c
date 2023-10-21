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

static void	ft_turn_left_right(t_game *game, t_player *player, int i)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(player->rot_speed * i)
		- player->dir_y * sin(player->rot_speed * i);
	player->dir_y = old_dir_x * sin(player->rot_speed * i)
		+ player->dir_y * cos(player->rot_speed * i);
	player->plane_x = player->plane_x * cos(player->rot_speed * i)
		- player->plane_y * sin(player->rot_speed * i);
	player->plane_y = old_plane_x * sin(player->rot_speed * i)
		+ player->plane_y * cos(player->rot_speed * i);
	ft_raycasting(game);
}

static void	ft_move_forward_backward(t_game *game, t_player *player, int i)
{
	if (game->map->map[(int)player->pos_y][(int)(player->pos_x
		+ i * player->dir_x * player->move_speed)] == '0')
		player->pos_x += i * player->dir_x * player->move_speed;
	if (game->map->map[(int)(player->pos_y + i * player->dir_y
			* player->move_speed)][(int)player->pos_x] == '0')
		player->pos_y += i * player->dir_y * player->move_speed;
	ft_raycasting(game);
}

static void	ft_move_left_right(t_game *game, t_player *player, int i)
{
	if (i == 1)
	{
		if (game->map->map[(int)player->pos_y][(int)(player->pos_x
			+ player->dir_y * player->move_speed)] == '0')
			player->pos_x += player->dir_y * player->move_speed;
		if (game->map->map[(int)(player->pos_y - player->dir_x
				* player->move_speed)][(int)player->pos_x] == '0')
			player->pos_y -= player->dir_x * player->move_speed;
	}
	else
	{
		if (game->map->map[(int)player->pos_y][(int)(player->pos_x
			- player->dir_y * player->move_speed)] == '0')
			player->pos_x -= player->dir_y * player->move_speed;
		if (game->map->map[(int)(player->pos_y + player->dir_x
				* player->move_speed)][(int)player->pos_x] == '0')
			player->pos_y += player->dir_x * player->move_speed;
	}
	ft_raycasting(game);
}

int	ft_hook(int keycode, t_game *game)
{
	if (keycode == ESC || keycode == ESC_L)
		ft_endgame(game);
	if (keycode == W || keycode == UP || keycode == W_L || keycode == UP_L)
		ft_move_forward_backward(game, game->player, 1);
	if (keycode == S || keycode == DOWN || keycode == S_L || keycode == DOWN_L)
		ft_move_forward_backward(game, game->player, -1);
	if (keycode == A || keycode == A_L)
		ft_move_left_right(game, game->player, 1);
	if (keycode == D || keycode == D_L)
		ft_move_left_right(game, game->player, 0);
	if (keycode == LEFT || keycode == LEFT_L)
		ft_turn_left_right(game, game->player, -1);
	if (keycode == RIGHT || keycode == RIGHT_L)
		ft_turn_left_right(game, game->player, 1);
	return (0);
}

int	ft_mouse_hook(int x, int y, t_game *game)
{
	mlx_mouse_hide();
	mlx_mouse_get_pos(game->win, &x, &y);
	if (x < SCREEN_WIDTH / 2)
		ft_turn_left_right(game, game->player, -1);
	else if (x > SCREEN_WIDTH / 2)
		ft_turn_left_right(game, game->player, 1);
	mlx_mouse_move(game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (0);
}
