/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 02:38:40 by olnytim           #+#    #+#             */
/*   Updated: 2023/10/16 17:57:18 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	ft_fc_colors(t_game *game, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	game->player->move_speed = 0.12;
	game->player->rot_speed = 0.1;
	(void)game;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			img->addr[y * SCREEN_WIDTH + x++] = game->ceiling_color;
		++y;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			img->addr[y * SCREEN_WIDTH + x++] = game->floor_color;
		++y;
	}
}

static void	ft_rays_init(t_game *game, t_rays *rays, int x)
{
	rays->time = 0;
	rays->old_time = 0;
	rays->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	rays->ray_dir_x = game->player->dir_x
		+ game->player->plane_x * rays->camera_x;
	rays->ray_dir_y = game->player->dir_y
		+ game->player->plane_y * rays->camera_x;
	rays->map_x = (int)game->player->pos_x;
	rays->map_y = (int)game->player->pos_y;
	if (rays->ray_dir_x == 0)
		rays->delta_dist_x = 1e30;
	else
		rays->delta_dist_x = fabs(1 / rays->ray_dir_x);
	if (rays->ray_dir_y == 0)
		rays->delta_dist_y = 1e30;
	else
		rays->delta_dist_y = fabs(1 / rays->ray_dir_y);
	rays->hit = 0;
}

static void	ft_step_calc(t_game *game, t_rays *rays)
{
	if (rays->ray_dir_x < 0)
	{
		rays->step_x = -1;
		rays->side_dist_x = (game->player->pos_x
				- rays->map_x) * rays->delta_dist_x;
	}
	else
	{
		rays->step_x = 1;
		rays->side_dist_x = (rays->map_x + 1.0
				- game->player->pos_x) * rays->delta_dist_x;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->step_y = -1;
		rays->side_dist_y = (game->player->pos_y
				- rays->map_y) * rays->delta_dist_y;
	}
	else
	{
		rays->step_y = 1;
		rays->side_dist_y = (rays->map_y + 1.0
				- game->player->pos_y) * rays->delta_dist_y;
	}
}

void	ft_raycasting(t_game *game)
{
	int		x;

	x = -1;
	game->img = malloc(sizeof(t_img));
	malloc_err(!game->img, "img");
	game->img->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img->addr = (int *)mlx_get_data_addr(game->img->img,
			&game->img->b_p_p, &game->img->line_length, &game->img->endian);
	ft_fc_colors(game, game->img);
	while (++x < SCREEN_WIDTH)
	{
		ft_rays_init(game, game->rays, x);
		ft_step_calc(game, game->rays);
		ft_dda(game, game->rays);
		ft_render_walls(game, game->rays, game->img);
		ft_walls_side(game, game->rays);
		ft_tex_rendering(game, game->rays, game->img, x);
	}
	mlx_clear_window(game->mlx, game->win);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	minimap(game, 4, 4);
	animation(game);
	mlx_destroy_image(game->mlx, game->img->img);
	free(game->img);
}
