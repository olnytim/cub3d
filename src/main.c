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

int	main(int ac, char **av)
{
	t_game	*game;
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	int	i = 200;
	int	j = 200;

	game = malloc(sizeof(t_game));
	ft_parse(game, ac, av);
	// system("leaks cub3D");
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Cub3D");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	ft_square(img, i, j);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
