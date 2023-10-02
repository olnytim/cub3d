/* ************************************************************************** */
/*                                                                            */
/*                                                    *._           _.*   @   */
/*   raycasting2.c                                      |\  \\_//  /|     #   */
/*                                                      \/         \/     $   */
/*   By: olnytim <yearagotomorrow@gmail.com>           _|_    V  V  |_    %   */
/*                                                  *=.    =  _*  =   .=* ^   */
/*   Created: 2023/10/02 15:21:10 by olnytim           \= ___________=/   &   */
/*   Updated: 2023/10/02 15:21:11 by olnytim                /     \       *   */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

void	ft_render_walls(t_game *game, t_rays *rays, t_img *img)
{
	rays->line_height = (int)(SCREEN_HEIGHT / rays->perp_wall_dist);
	img->draw_start = (-rays->line_height / 2 + SCREEN_HEIGHT / 2);
	if (img->draw_start < 0)
		img->draw_start = 0;
	img->draw_end = (rays->line_height / 2 + SCREEN_HEIGHT / 2);
	if (img->draw_end >= SCREEN_HEIGHT)
		img->draw_end = SCREEN_HEIGHT - 1;
	if (rays->side == 1)
		img->color = img->color / 2;
	if (side == 0)
		rays->wall_X = game->player->pos_y + rays->perp_wall_dist
			* rays->ray_dir_y;
	else
		rays->wall_x = game->player->pos_x + rays->perp_wall_dist
			* rays->ray_dir_x;
	rays->wall_x -= floor(wall_x);
	rays->tex_x = (int)(rays->wall_x * (double)game->wall_t->width);
	if (rays->side == 0 && rays->ray_dir_x > 0)
		rays->tex_x = game->wall_t->width - rays->tex_x - 1;
	if (rays->side == 1 && rays->ray_dir_y < 0)
		rays->tex_x = game->wall_t->width - rays->tex_x - 1;
}

void	ft_fc_colors(t_game *game, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			img->addr[y * SCREEN_HEIGHT + x++] = game->ceiling_color;
		++y;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			img->addr[y * SCREEN_HEIGHT + x++] = game->floor_color;
		++y;
	}
}

void	ft_walls_side(t_game *game, t_rays *rays)
{
	if (rays->side == 0)
	{
		if (rays->ray_dir_x > 0)
			game->wall_t = game->e;
		else
			game->wall_t = game->w;
	}
	else
	{
		if (rays->ray_dir_y > 0)
			game->wall_t = game->n;
		else
			game->wall_t = game->s;
	}
}

void	ft_tex_rendering(t_game *game, t_rays *rays, t_img *img, int *x)
{
	int	y;

	rays->tex_height = (int)(SCREEN_HEIGHT / rays->perp_wall_dist);
	img->drawstart = -rays->tex_height / 2 + SCREEN_HEIGHT / 2;
	if (img->drawstart < 0)
		img->drawstart = 0;
	img->drawend = -rays->tex_height / 2 + SCREEN_HEIGHT / 2;
	if (img->drawend < 0)
		img->drawend = SCREEN_HEIGHT - 1;
	y = img->drawstart;
	while (y < img->drawend)
	{
		rays->tex_y = (int)(((y - SCREEN_HEIGHT / 2 + rays->tex_height / 2) \
			* game->wall_t->height) / rays->text_height);
		img->color = game->wall_t->addr[rays->tex_y * game->wall_t->width
			+ rays->tex_x];
		game->img->addr[y * SCREEN_WIDTH + x] = img->color;
		++y;
	}
}
