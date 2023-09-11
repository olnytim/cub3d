/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:10:58 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/11 02:11:00 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

void	ft_check_end(t_game *game)
{
	char	*line;

	line = get_next_line(game->mapinfo->fd);
	if (!*line)
		return ;
	while (*line && line)
	{
		if (*line == '\n')
		{
			free(line);
			line = get_next_line(game->mapinfo->fd);
		}
		else if (*line != '\n')
		{
			free(line);
			ft_exit("Wrong map\nUse correct one\n");
		}
	}
	free(line);
}

void	ft_path_parse(t_game *game)
{
	char	*line;

	line = ft_strdup("NSWECF");
	game->mapinfo->line = get_next_line(game->mapinfo->fd);
	if (!game->mapinfo->line)
		ft_exit("File is empty\n");
	while (!ft_check_path_color(line))
	{
		free(game->mapinfo->line);
		game->mapinfo->line = get_next_line(game->mapinfo->fd);
		if (!game->mapinfo->line)
			ft_exit("File is empty\n");
	}
}
