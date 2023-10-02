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

#include "../hf/cub3d.h"

static void	ft_player_init(t_game *game, t_player *player)
{
	if (game->mapinfo->dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (game->mapinfo->dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (game->mapinfo->dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	player->plane_x = 0;
	player->plane_y = 0.66;
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
	return (rays);
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

static void	ft_dda(t_game *game, t_rays *rays)
{
	while (rays->hit == 0)
	{
		if (rays->side_dist_x < rays->side_dist_y)
		{
			rays->side_dist_x += rays->delta_dist_x;
			rays->map_x += rays->step_x;
			rays->side = 0;
		}
		else
		{
			rays->side_dist_y += rays->delta_dist_y;
			rays->map_y += rays->step_y;
			rays->side = 1;
		}
		if (game->mapinfo->map[rays->map_x][rays->map_y])
			rays->hit = 1;
	}
	if (rays->side == 0)
		rays->perp_wall_dist = (rays->side_dist_x
				- rays->delta_dist_x);
	else
		rays->perp_wall_dist = (rays->side_dist_y
				- rays->delta_dist_y);
}

void	ft_raycasting(t_game *game)
{
	int		x;

	x = 0;
	ft_fc_colors(game, game->img);
	ft_player_init(game, game->player);
	game->img = malloc(sizeof(t_img));
	game->img->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->img, game->img->b_p_p, \
			game->img->line_length, game->img->endian);
	game->rays = malloc(sizeof(t_rays));
	malloc_err(rays, "rays");
	while (x < SCREEN_WIDTH)
	{
		ft_rays_init(game, game->rays, &x);
		ft_step_calc(game, game->rays);
		ft_dda(game, game->rays);
		ft_render_walls(game, game->rays, game->img);
		ft_walls_side(game, game->rays);
		ft_tex_rendering(game, game->rays, game->img, &x);
		++x;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img->img);
	free(game->img);
}
