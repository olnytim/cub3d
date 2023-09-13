/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:10:51 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/11 02:10:53 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

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
		game->mapinfo->fd = fd;
		// close(fd);
	}
	else
		ft_exit("Wrong number of args\n");
}
