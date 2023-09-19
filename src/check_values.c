/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:31:41 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/19 16:14:34 by tgalyaut         ###   ########.fr       */
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
	map = ft_skip_spaces(map);
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

// static int	ft_check_chars(t_game *game, char **line)
// {
// 	static int	flag;
// 	char		*temp;

// 	flag = 0;
// 	*line = ft_strtrim(*line, "\n");
// 	temp = *line;
// 	while (*temp)
// 	{
// 		if ((*temp == 'N' || *temp == 'E' || *temp == 'W'
// 			|| *temp == 'S') && flag == 0)
// 		{
// 			flag = 1;
// 			game->mapinfo->dir = *temp;
// 		}
// 		else if (*temp != '1' && *temp != '0' && *temp != ' ')
// 			ft_exit("Invalid chars\n");
// 		++temp;
// 	}
// 	return (1);
// }

void	count_lines(t_game *game, int *amount) 
{
	char	buffer[2];
	char	prev_char = '\0';

	while (read(game->mapinfo->fd, buffer, 1) > 0)
	{
		if (buffer[0] == '\n')
			(*amount)++;
		prev_char = buffer[0];
		buffer[1] = '\0';
	}
	if (prev_char != '\n')
		(*amount)++;
}

void	ft_map_parse(t_game *game, char *line)
{
	int	amount;

	amount = 1;
	while (*line == '\n')
	{
		free(line);
		line = get_next_line(game->mapinfo->fd);
	}
	if (!line)
		ft_exit("There is no map in file!\n");
	count_lines(game, &amount);
	printf("amount is: %d\n", amount);
	// now try to count lines of map
	// while (ft_check_chars(game, &line))
	// {
	// }
}

void	ft_path_parse(t_game *game)
{
	char	*line;

	line = ft_strdup("NSEWCF");
	game->mapinfo->line = get_next_line(game->mapinfo->fd);
	if (!game->mapinfo->line)
		ft_exit("File is empty\n");
	while (!ft_check_path_color(line)
		&& ft_check_lines(game, game->mapinfo->line, line))
	{
		free(game->mapinfo->line);
		game->mapinfo->line = get_next_line(game->mapinfo->fd);
		if (!game->mapinfo->line)
			ft_exit("File is empty\n");
	}
	free(line);
	ft_map_parse(game, game->mapinfo->line);
}
