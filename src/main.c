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

int	main(int ac, char **av)
{
	t_game	*game;
	void	*mlx;

	game = malloc(sizeof(t_game));
	ft_parse(game, ac, av);
	// system("leaks cub3D");
	mlx = mlx_init();
	mlx_new_window(mlx, 500, 500, "Minilibx test");
	mlx_loop(mlx);
	return (0);
}
