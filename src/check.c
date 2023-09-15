/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:13:57 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/15 22:27:03 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// file will contain each parse and init function

#include "../hf/cub3d.h"

void	ft_print_info(t_game *game)
{
	ft_printf("fd is: %d\n", game->mapinfo->fd);
	ft_printf("no is: %s", game->mapinfo->n_path);
	ft_printf("so is: %s", game->mapinfo->s_path);
	ft_printf("eo is: %s", game->mapinfo->e_path);
	ft_printf("wo is: %s", game->mapinfo->w_path);
}

void	ft_parse(t_game *game, int ac, char **av)
{
	ft_sizes(game, ac, av);
	ft_path_parse(game);
	ft_print_info(game);
}
