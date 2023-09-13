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
		game->mapinfo->n_path = ft_strdup(line);
	else if (rem == 'S')
		game->mapinfo->s_path = ft_strdup(line);
	else if (rem == 'E')
		game->mapinfo->e_path = ft_strdup(line);
	else if (rem == 'W')
		game->mapinfo->w_path = ft_strdup(line);
	else if (rem == 'C')
		game->mapinfo->c_color = ft_strdup(line);
	else if (rem == 'F')
		game->mapinfo->f_color = ft_strdup(line);
	// ft_print_info(game);
	return (1);
}

static int	ft_check_lines(t_game *game, char *map, char* line)
{
	if (*map == '\n')
		return (1);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (ft_init_dirs(game, map, line + 2, 'N'));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (ft_init_dirs(game, map, line + 2, 'S'));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (ft_init_dirs(game, map, line + 2, 'E'));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (ft_init_dirs(game, map, line + 2, 'W'));
	else if (line[0] == 'C' && line[1] == ' ')
		return (ft_init_dirs(game, map, line + 1, 'C'));
	else if (line[0] == 'F' && line[1] == ' ')
		return (ft_init_dirs(game, map, line + 1, 'F'));
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
