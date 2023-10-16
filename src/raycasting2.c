/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:21:10 by olnytim           #+#    #+#             */
/*   Updated: 2023/10/16 16:49:24 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <cub3D.h>

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
		if (game->map->map[rays->map_y][rays->map_x] == '1')
			rays->hit = 1;
	}
	if (rays->side == 0)
		rays->perp_wall_dist = (rays->side_dist_x
				- rays->delta_dist_x);
	else
		rays->perp_wall_dist = (rays->side_dist_y
				- rays->delta_dist_y);
}

void	ft_render_walls(t_game *game, t_rays *rays, t_img *img)
{
	rays->line_height = (int)(SCREEN_HEIGHT / rays->perp_wall_dist);
	img->draw_start = -rays->line_height / 2 + SCREEN_HEIGHT / 2;
	if (img->draw_start < 0)
		img->draw_start = 0;
	img->draw_end = rays->line_height / 2 + SCREEN_HEIGHT / 2;
	if (img->draw_end >= SCREEN_HEIGHT)
		img->draw_end = SCREEN_HEIGHT - 1;
	if (rays->side == 1)
		img->color = img->color / 2;
	if (rays->side == 0)
		rays->wall_x = game->player->pos_y + rays->perp_wall_dist
			* rays->ray_dir_y;
	else
		rays->wall_x = game->player->pos_x + rays->perp_wall_dist
			* rays->ray_dir_x;
	rays->wall_x -= floor(rays->wall_x);
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
	rays->tex_x = (int)(rays->wall_x * (double)game->wall_t->width);
	if ((rays->side == 0 && rays->ray_dir_x > 0)
		|| (rays->side == 1 && rays->ray_dir_y < 0))
		rays->tex_x = game->wall_t->width - rays->tex_x - 1;
}

void	ft_tex_rendering(t_game *game, t_rays *rays, t_img *img, int x)
{
	double	tex_pos;
	double	step;

	step = 1.0 * game->wall_t->height / rays->line_height;
	tex_pos = (img->draw_start - SCREEN_HEIGHT / 2 + rays->line_height / 2)
		* step;
	while (img->draw_start < img->draw_end)
	{
		rays->tex_y = (int)tex_pos & (game->wall_t->height - 1);
		tex_pos += step;
		img->color = game->wall_t->addr[rays->tex_y * game->wall_t->height
			+ rays->tex_x];
		if (rays->side == 1)
			img->color = (img->color >> 1) & 8355711;
		img->addr[img->draw_start * SCREEN_WIDTH + x] = img->color;
		++img->draw_start;
	}
}
