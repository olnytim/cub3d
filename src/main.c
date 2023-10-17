/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:12:27 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/10/16 16:48:19 by tgalyaut         ###   ########.fr       */
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
			player->plane_x = 0.66;
		}
	}
	else
	{
		player->dir_y = 0;
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

static void	ft_sides_init(t_game *game, int i)
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
		img->addr = (int *)mlx_get_data_addr(img->img, &img->b_p_p,
				&img->line_length, &img->endian);
		*img_pointers[i] = img;
	}
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	int	*dst;

	dst = game->img->addr + (y * game->img->line_length
			+ x * (game->img->b_p_p / 8));
	*(unsigned int *)dst = color;
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	ft_parse(game, ac, av);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	ft_player_init(game, game->player);
	ft_sides_init(game, -1);
	ft_raycasting(game);
	mlx_hook(game->win, 17, 0, ft_endgame, game);
	mlx_hook(game->win, 2, 1L << 0, ft_hook, game);
	mlx_mouse_hook(game->win, ft_mouse_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
