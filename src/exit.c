/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:33:58 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/11 02:34:00 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <cub3D.h>

void	ft_exit(char *str)
{
	ft_printf("%s", str);
	exit(1);
}

void	malloc_err(int condition, char *str)
{
	if (condition)
	{
		printf("cub3D: malloc error: %s\n", str);
		exit(1);
	}
}

int	ft_endgame(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	printf("Game Over!\n");
	exit(0);
}
