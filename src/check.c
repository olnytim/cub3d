/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:13:57 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/10/16 16:50:08 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	ft_print_info(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("player dir is: %c\n", game->map->dir);
	printf("player pos_x: %f\n", game->player->pos_x);
	printf("player pos_y: %f\n", game->player->pos_y);
	ft_printf("ceiling color is: %d\n", game->ceiling_color);
	ft_printf("floor color is: %d\n", game->floor_color);
	while (i < game->map->map_size)
	{
		j = 0;
		ft_printf("map[%d] is: ", i);
		while (j < (int)ft_strlen(game->map->map[i]))
		{
			ft_printf("%c", game->map->map[i][j]);
			++j;
		}
		printf("\n");
		++i;
	}
}
