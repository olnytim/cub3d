/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:12:27 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/19 16:13:58 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(int ac, char **av)
{
	t_game	*game;
	t_img	img;

	game = malloc(sizeof(t_game));
	ft_parse(game, ac, av);
	// system("leaks cub3D");
	// init mlx win
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 500, 500, "Cub3D");
	// draw smth
	// img.img = mlx_new_image(game->mlx, 500, 500);
	// img.addr = mlx_get_data_addr(img.img,
	// 		&img.bits_per_pixel, &img.line_length, &img.endian);
	// ft_square(img, i, j);
	// ft_drawCharInCircle(&img, i + 50, j + 50, 100, 0x00FF0000);
	// mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	// hooks
	// mlx_hook(game->win, 17, 0, ft_endgame, game);
	// mlx_hook(game->win, 2, 1L << 0, ft_hook, game);
	// mlx_mouse_hook(game->win, ft_mouse_hook, game);
	// mlx_loop(game->mlx);
	return (0);
}
