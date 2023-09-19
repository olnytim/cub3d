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

// static void	ft_check_end(t_game *game)
// {
// 	char	*line;

// 	line = get_next_line(game->mapinfo->fd);
// 	if (!*line)
// 		return ;
// 	while (*line && line)
// 	{
// 		if (*line == '\n')
// 		{
// 			free(line);
// 			line = get_next_line(game->mapinfo->fd);
// 		}
// 		else if (*line != '\n')
// 		{
// 			free(line);
// 			ft_exit("Wrong map\nUse correct one\n");
// 		}
// 	}
// 	free(line);
// }

static int	ft_check_chars(t_game *game, char **line)
{
	static int	flag;
	char		*temp;
	int			i;

	i = 0;
	*line = ft_strtrim(*line, "\n");
	temp = *line;
	while (*temp)
	{
		if ((*temp == 'N' || *temp == 'E' || *temp == 'W'
				|| *temp == 'S') && flag == 0)
		{
			flag = 1;
			game->mapinfo->dir = *temp;
		}
		else if (*temp != '1' && *temp != '0' && *temp != ' ')
			ft_exit("Invalid chars\n");
		++temp;
	}
	return (1);
}

static void	count_lines(t_game *game, int *amount)
{
	char	buffer[2];
	char	prev_char;

	prev_char = '\0';
	while (read(game->mapinfo->fd, buffer, 1) > 0)
	{
		if (buffer[0] == '\n')
			(*amount)++;
		prev_char = buffer[0];
		buffer[1] = '\0';
	}
	if (prev_char != '\n')
		(*amount)++;
	close(game->mapinfo->fd);
}

static void	ft_add_lines(t_game *game, char *line)
{
	static int	i;

	game->mapinfo->map[i] = ft_strdup(line);
	free(line);
	printf("map[%d] is: %s\n", i, game->mapinfo->map[i]);
	++i;
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
	game->mapinfo->map = malloc(sizeof(char *) * (amount + 2));
	if (!game->mapinfo->map)
		ft_exit("Malloc error\n");
	while (ft_check_chars(game, &line))
	{
		ft_add_lines(game, line);
		line = get_next_line(game->mapinfo->fd);
		if (!line)
			break ;
			//err
	}
	game->mapinfo->map[amount + 1] = NULL;
}
