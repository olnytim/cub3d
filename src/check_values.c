/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:31:41 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/19 16:45:59 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

static int	ft_init_dirs(t_game *game, char *map, char *line, char rem)
{
	while (*line != rem && *line)
		++line;
	if (!*line)
		ft_exit("Error\n");
	*line = ' ';
	map = ft_skip_spaces(map);
	if (!*map || *map == '\n')
		ft_exit("Input invalid path for orientation\n");
	if (rem == 'N')
		game->map->n_path = ft_strtrim(ft_strdup(map), "\n");
	else if (rem == 'S')
		game->map->s_path = ft_strtrim(ft_strdup(map), "\n");
	else if (rem == 'E')
		game->map->e_path = ft_strtrim(ft_strdup(map), "\n");
	else if (rem == 'W')
		game->map->w_path = ft_strtrim(ft_strdup(map), "\n");
	else if (rem == 'C')
		game->map->c_color = ft_strtrim(ft_strdup(map), "\n");
	else if (rem == 'F')
		game->map->f_color = ft_strtrim(ft_strdup(map), "\n");
	return (1);
}

static int	ft_check_lines(t_game *game, char *map, char *line)
{
	if (*map == '\n')
		return (1);
	if (map[0] == 'N' && map[1] == 'O' && map[2] == ' ')
		return (ft_init_dirs(game, map + 2, line, 'N'));
	else if (map[0] == 'S' && map[1] == 'O' && map[2] == ' ')
		return (ft_init_dirs(game, map + 2, line, 'S'));
	else if (map[0] == 'E' && map[1] == 'A' && map[2] == ' ')
		return (ft_init_dirs(game, map + 2, line, 'E'));
	else if (map[0] == 'W' && map[1] == 'E' && map[2] == ' ')
		return (ft_init_dirs(game, map + 2, line, 'W'));
	else if (map[0] == 'C' && map[1] == ' ')
		return (ft_init_dirs(game, map + 1, line, 'C'));
	else if (map[0] == 'F' && map[1] == ' ')
		return (ft_init_dirs(game, map + 1, line, 'F'));
	else
		ft_exit("Use correct orientation\n");
	return (0);
}

void	ft_path_parse(t_game *game)
{
	char	*line;

	line = ft_strdup("NSEWCF");
	game->map->line = get_next_line(game->map->fd);
	game->map->raws_count = 1;
	game->player->pos_x = 0;
	game->player->pos_y = 0;
	if (!game->map->line)
		ft_exit("File is empty\n");
	while (!ft_check_path_color(line)
		&& ft_check_lines(game, game->map->line, line))
	{
		free(game->map->line);
		game->map->line = get_next_line(game->map->fd);
		++game->map->raws_count;
		if (!game->map->line)
			ft_exit("File is empty\n");
	}
	free(line);
	ft_convert_colors(game);
	ft_map_parse(game, game->map->line);
}
