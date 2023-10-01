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

void	ft_player_init(t_game *game, t_player *player)
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

t_rays	*ft_rays_init(t_game *game, int *x)
{
	t_rays	*rays;

	rays = malloc(sizeof(t_rays));
	malloc_err(rays, "rays");
	rays->time = 0;
	rays->old_time = 0;
	rays->camera_x = 2 * x / SCREEN_WIDTH - 1;
	rays->ray_dir_x = game->player->dir_x
		+ game->player->plane_x * rays->camera_x;
	rays->ray_dir_y = game->player->dir_y
		+ game->player->plane_y * rays->camera_x;
	rays->map_x = int (game->player->pos_x);
	rays->map_y = int (game->player->pos_y);
	rays->delta_dist_x = (rays->ray_dir_x == 0)
		? 1e30 : fabs(1 / rays->ray_dir_x);
	rays->delta_dist_y = (rays->ray_dir_y == 0)
		? 1e30 : fabs(1 / rays->ray_dir_y);
	rays->hit = 1;
	return (rays);
}

void	ft_step_calc(t_game *game, t_rays *rays)
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

void	ft_dda(t_game *game, t_rays *rays)
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
	int	x;

	x = 0;
	ft_player_init(game, game->player);
	while (x < SCREEN_WIDTH)
	{
		game->rays = ft_rays_init(game, &x);
		ft_step_calc(game, game->rays);
		ft_dda(game, game->rays);
		ft_draw_line(); // not done yet
	}
}
