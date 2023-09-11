/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:13:57 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/11 02:13:59 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// file will contain each parse and init function

#include "../hf/cub3d.h"

static void	ft_print_info(t_game *game)
{
	ft_printf("fd is: %d\n", game->mapinfo->fd);
}

void	ft_parse(t_game *game, int ac, char **av)
{
	ft_sizes(game, ac, av);
	ft_print_info(game);
}
