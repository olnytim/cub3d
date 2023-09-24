/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:13:57 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/19 16:41:39 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// file will contain each parse and init function

#include "../hf/cub3d.h"

void	ft_print_info(t_game *game)
{
	ft_printf("fd is: %d\n", game->mapinfo->fd);
	ft_printf("raws_count is: %d\n", game->mapinfo->raws_count);
	ft_printf("map size is: %d\n", game->mapinfo->map_size);
	ft_printf("address is: %s\n", game->mapinfo->address);
	ft_printf("no is: %s", game->mapinfo->n_path);
	ft_printf("so is: %s", game->mapinfo->s_path);
	ft_printf("eo is: %s", game->mapinfo->e_path);
	ft_printf("wo is: %s", game->mapinfo->w_path);
	ft_printf("fc is: %s", game->mapinfo->f_color);
	ft_printf("cc is: %s", game->mapinfo->c_color);
}

void	ft_sizes(t_game *game, int ac, char **av)
{
	int			fd;
	char		*name;
	t_mapinfo	*mapinfo;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
			ft_exit("Wrong file\nTry to use correct file\n");
		name = ft_strrchr(av[1], '.');
		if (!name || ft_strncmp(name, ".cub", 5) != 0)
			ft_exit("Try to use file with '.cub' ending\n");
		mapinfo = malloc(sizeof(t_mapinfo));
		if (!mapinfo)
			ft_exit("Malloc error\n");
		game->mapinfo = mapinfo;
		game->mapinfo->address = ft_strdup(av[1]);
		game->mapinfo->fd = fd;
	}
	else
		ft_exit("Wrong number of args\n");
}

void	ft_parse(t_game *game, int ac, char **av)
{
	ft_sizes(game, ac, av);
	ft_path_parse(game);
	ft_print_info(game);
}
