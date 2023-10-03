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

#include "../include/cub3D.h"
#include <cub3D.h>

static int	ft_init_dirs(t_game *game, char *map, char *line, char rem)
{
	char	*tmp;

	while (*line != rem && *line)
		++line;
	if (!*line)
		ft_exit("Error\n");
	*line = ' ';
	map = ft_skip_spaces(map);
	if (!*map || *map == '\n')
		ft_exit("Input invalid path for orientation\n");
	//It can all be one function
	if (rem == 'N')
	{
		tmp = ft_strdup(map);
		malloc_err(!tmp, "idk");		//TIMUUUUURRRRR!!!! Error!!!
		game->map->n_path = ft_strtrim(tmp, "\n");
		free(tmp);
		malloc_err(!game->map->n_path, "idk");		//TIMUUUUURRRRR!!!! Error!!!
	}
	else if (rem == 'S')
	{
		tmp = ft_strdup(map);
		malloc_err(!tmp, "idk");		//TIMUUUUURRRRR!!!! Error!!!
		game->map->s_path = ft_strtrim(tmp, "\n");
		free(tmp);
		malloc_err(!game->map->s_path, "idk");		//TIMUUUUURRRRR!!!! Error!!!
	}
	else if (rem == 'E')
	{
		tmp = ft_strdup(map);
		malloc_err(!tmp, "idk");		//TIMUUUUURRRRR!!!! Error!!!
		game->map->e_path = ft_strtrim(tmp, "\n");
		free(tmp);
		malloc_err(!game->map->e_path, "idk");		//TIMUUUUURRRRR!!!! Error!!!
	}
	else if (rem == 'W')
	{
		tmp = ft_strdup(map);
		malloc_err(!tmp, "idk");		//TIMUUUUURRRRR!!!! Error!!!
		game->map->w_path = ft_strtrim(tmp, "\n");
		free(tmp);
		malloc_err(!game->map->w_path, "idk");		//TIMUUUUURRRRR!!!! Error!!!
	}
	else if (rem == 'C')
	{
		tmp = ft_strdup(map);
		malloc_err(!tmp, "idk");		//TIMUUUUURRRRR!!!! Error!!!
		game->map->c_color = ft_strtrim(tmp, "\n");
		free(tmp);
		malloc_err(!game->map->c_color, "idk");		//TIMUUUUURRRRR!!!! Error!!!
	}
	else if (rem == 'F')
	{
		tmp = ft_strdup(map);
		malloc_err(!tmp, "idk");		//TIMUUUUURRRRR!!!! Error!!!
		game->map->f_color = ft_strtrim(tmp, "\n");
		free(tmp);
		malloc_err(!game->map->f_color, "idk");		//TIMUUUUURRRRR!!!! Error!!!
	}
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
