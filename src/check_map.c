/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:10:51 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/19 17:49:11 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

static int	ft_check_end(t_game *game, char *line)
{
	while (*line)
	{
		if (*line == '\n')
		{
			free(line);
			line = get_next_line(game->map->fd);
			if (!line)
				return (1);
		}
		else if (*line != '\n')
		{
			free(line);
			ft_exit("Wrong map\nUse correct one\n");
		}
	}
	free(line);
	return (0);
}

static int	ft_check_chars(t_game *game, char **line)
{
	static int	flag;
	char		*temp;

	if (!*line)
		return (0);
	temp = ft_strtrim(*line, "\n");
	free(*line);
	*line = temp;
	temp = *line;
	while (*temp)
	{
		if ((*temp == 'N' || *temp == 'E' || *temp == 'W'
				|| *temp == 'S') && flag == 0)
		{
			flag = 1;
			game->map->dir = *temp;
		}
		else if (*temp != '1' && *temp != '0' && *temp != ' ')
			ft_exit("Invalid chars\n");
		++temp;
	}
	return (1);
}

static void	count_lines(t_game *game, char **line)
{
	game->map->map_size = 0;
	while (*line)
	{
		game->map->map_size++;
		free(*line);
		*line = get_next_line(game->map->fd);
	}
	close(game->map->fd);
	game->map->fd = open(game->map->address, O_RDONLY);
	if (game->map->fd < 0)
		ft_exit("Wrong file\nTry to use correct file\n");
	while (game->map->raws_count--)
	{
		free(*line);
		*line = get_next_line(game->map->fd);
	}
}

static void	ft_add_lines(t_game *game, char *line)
{
	static int	i;

	game->map->map[i] = line;
	printf("map[%d] is: %s\n", i, game->map->map[i]);
	++i;
}

void	ft_map_parse(t_game *game, char *line)
{
	while (*line == '\n')
	{
		free(line);
		++game->map->raws_count;
		line = get_next_line(game->map->fd);
	}
	if (!line)
		ft_exit("There is no map in file!\n");
	count_lines(game, &line);
	game->map->map = malloc(sizeof(char *)
			* (game->map->map_size + 1));
	malloc_err(!game->map->map, "map");
	while (ft_check_chars(game, &line))
	{
		ft_add_lines(game, line);
		line = get_next_line(game->map->fd);
		if (!line)
			break ;
		if (*line == '\n' && ft_check_end(game, line))
			break ;
	}
	game->map->map[game->map->map_size] = NULL;
	ft_check_fence(game, 0, 0);
}
