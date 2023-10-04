/* ************************************************************************** */
/*                                                                            */
/*                                                    *._           _.*   @   */
/*   raycasting.c                                       |\  \\_//  /|     #   */
/*                                                      \/         \/     $   */
/*   By: olnytim <yearagotomorrow@gmail.com>           _|_    V  V  |_    %   */
/*                                                  *=.    =  _*  =   .=* ^   */
/*   Created: 2023/10/02 02:38:40 by olnytim           \= ___________=/   &   */
/*   Updated: 2023/10/02 02:38:42 by olnytim                /     \       *   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <cub3D.h>

static void	ft_player_init(t_game *game, t_player *player)
{
	if (game->map->dir == 'N' || game->map->dir == 'S')
	{
		player->dir_x = 0;
		player->plane_y = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		if (game->map->dir == 'N')
		{
			player->dir_y = -1;
			player->plane_x = -0.66;
		}
	}
	else
	{
		layer->dir_y = 0;
		player->plane_x = 0;
		player->dir_x = -1;
		player->plane_y = 0.66;
		if (game->map->dir == 'E')
		{
			player->dir_x = 1;
			player->plane_y = -0.66;
		}
	}
}

static void	ft_rays_init(t_game *game, t_rays *rays, int *x)
{
	rays->time = 0;
	rays->old_time = 0;
	rays->camera_x = 2 * *x / SCREEN_WIDTH - 1;
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

void	ft_sides_init(t_game *game, int i)
{
	char	*img_path[4];
	t_img	**img_pointers[4];
	t_img	*img;

	img_path[0] = game->map->n_path;
	img_path[1] = game->map->s_path;
	img_path[2] = game->map->w_path;
	img_path[3] = game->map->e_path;
	img_pointers[0] = &game->n;
	img_pointers[1] = &game->s;
	img_pointers[2] = &game->w;
	img_pointers[3] = &game->e;
	while (++i < 4)
	{
		img = malloc(sizeof(t_img));
		malloc_err(!img, "problem with creating img");
		img->img = mlx_xpm_file_to_image(game->mlx, img_path[i],
				&img->width, &img->height);
		ft_img_check(img);
		img->addr = mlx_get_data_addr(img->img, &img->b_p_p,
				&img->line_length, &img->endian);
		*img_pointers[i] = img;
	}
}

void	ft_raycasting(t_game *game)
{
	int		x;

	x = -1;
	game->img = malloc(sizeof(t_img));
	malloc_err(!game->img, "img");
	game->img->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->b_p_p, \
			&game->img->line_length, &game->img->endian);
	ft_fc_colors(game, game->img);
	ft_player_init(game, game->player);
	game->rays = malloc(sizeof(t_rays));
	malloc_err(!game->rays, "rays");
	ft_sides_init(game, -1);
	while (++x < SCREEN_WIDTH)
	{
		ft_rays_init(game, game->rays, &x);
		ft_step_calc(game, game->rays);
		ft_dda(game, game->rays);
		ft_walls_side(game, game->rays);
		ft_render_walls(game, game->rays, game->img);
		ft_tex_rendering(game, game->rays, game->img, &x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img->img);
	free(game->img);
}
