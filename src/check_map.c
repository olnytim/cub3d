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
	char	*temp;
	int		i;

	line = ft_strdup("NSWECF");
	while (game->mapinfo->height > 0)
	{
		free(temp);
		temp = get_next_line(game->mapinfo->fd);
		ft_empty(temp);
		i = 0;
		while (temp[i] != '\n' && temp)
		{
			i = ft_skip_spaces(temp);
//			if (temp[i] == 'N')

		}
	}
}
