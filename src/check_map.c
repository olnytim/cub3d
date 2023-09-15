/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 02:10:58 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/15 22:17:08 by tgalyaut         ###   ########.fr       */
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

static int	ft_init_dirs(t_game *game, char *map, char *line, char rem)
{
	while (*line != rem && *line)
		++line;
	if (!*line)
		ft_exit("Error\n");
	*line = ' ';
	ft_skip_spaces(map);
	if (!*map || *map == '\n')
		ft_exit("Input invalid path for orientation\n");
	if (rem == 'N')
		game->mapinfo->n_path = ft_strdup(map);
	else if (rem == 'S')
		game->mapinfo->s_path = ft_strdup(map);
	else if (rem == 'E')
		game->mapinfo->e_path = ft_strdup(map);
	else if (rem == 'W')
		game->mapinfo->w_path = ft_strdup(map);
	else if (rem == 'C')
		game->mapinfo->c_color = ft_strdup(map);
	else if (rem == 'F')
		game->mapinfo->f_color = ft_strdup(map);
	// ft_print_info(game);
	return (1);
}

static int	ft_check_lines(t_game *game, char *map, char* line)
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
	game->mapinfo->line = get_next_line(game->mapinfo->fd);
	ft_printf("fd is: %d\n", game->mapinfo->fd);
	ft_printf("line is: '%s'", game->mapinfo->line);
	if (!game->mapinfo->line)
		ft_exit("File is empty\n");
	while (!ft_check_path_color(line) && ft_check_lines(game, game->mapinfo->line, line))
	{
		free(game->mapinfo->line);
		game->mapinfo->line = get_next_line(game->mapinfo->fd);
		ft_printf("line is: '%s'\n", game->mapinfo->line);
		if (!game->mapinfo->line)
			ft_exit("File is empty\n");
	}
}
