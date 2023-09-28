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

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_square(t_data img, int i, int j)
{
	while (i < 300)
		my_mlx_pixel_put(&img, ++i, j, 0x00FF0000);
	while (j < 300)
		my_mlx_pixel_put(&img, i, ++j, 0x00FF0000);
	while (i > 200)
		my_mlx_pixel_put(&img, --i, j, 0x00FF0000);
	while (j > 200)
		my_mlx_pixel_put(&img, i, --j, 0x00FF0000);
}

void	drawCharInCircle(t_data *img, int centerX,\
		int centerY, int radius, int color)
{
	int x = radius;
	int y = 0;
	int decisionOver2 = 1 - x;

	while (y <= x)
	{
		my_mlx_pixel_put(img, centerX + x, centerY + y, color);
		my_mlx_pixel_put(img, centerX - x, centerY + y, color);
		my_mlx_pixel_put(img, centerX + x, centerY - y, color);
		my_mlx_pixel_put(img, centerX - x, centerY - y, color);
		my_mlx_pixel_put(img, centerX + y, centerY + x, color);
		my_mlx_pixel_put(img, centerX - y, centerY + x, color);
		my_mlx_pixel_put(img, centerX + y, centerY - x, color);
		my_mlx_pixel_put(img, centerX - y, centerY - x, color);
		y++;
		if (decisionOver2 <= 0) {
			decisionOver2 += 2 * y + 1;
		} else {
			x--;
			decisionOver2 += 2 * (y - x) + 1;
		}
	}
	int charX = centerX - 4;
	int charY = centerY - 4;
	my_mlx_pixel_put(img, charX + 2, charY, color);
	my_mlx_pixel_put(img, charX + 1, charY + 1, color);
	my_mlx_pixel_put(img, charX + 3, charY + 1, color);
	my_mlx_pixel_put(img, charX, charY + 2, color);
	my_mlx_pixel_put(img, charX + 4, charY + 2, color);
}

int	ft_hook(int keycode, t_game *game)
{
	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		ft_endgame(game);
	// if (keycode == W)
	// 	;
	// if (keycode == S)
	// 	;
	// if (keycode == D)
	// 	;
	// if (keycode == A)
	// 	;
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_game *game)
{
	(void)game;
	// int	x;
	// int	y;
	// mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	printf("keycode: %d\n", button);
	printf("Mouse Position: X = %d, Y = %d\n", x, y);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;
	t_data	img;

	int	i = 200;
	int	j = 200;

	game = malloc(sizeof(t_game));
	ft_parse(game, ac, av);
	// system("leaks cub3D");
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 500, 500, "Cub3D");
	img.img = mlx_new_image(game->mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_square(img, i, j);
	drawCharInCircle(&img, i + 50, j + 50, 100, 0x00FF0000);
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	mlx_hook(game->win, 17, 0, ft_endgame, game);
	mlx_hook(game->win, 2, 1L<<0, ft_hook, game);
	mlx_mouse_hook(game->win, ft_mouse_hook, game);
	// while (1)
	// {
	// 	mlx_mouse_hook(game->win, ft_mouse_hook, game);
	// 	usleep(100000);
	// }
	mlx_loop(game->mlx);
	return (0);
}
