/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:22:58 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/15 22:39:14 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

char	*ft_skip_spaces(char *line)
{
	while (*line == ' ')
		++line;
	return (line);
}

void	check_position(char pos, char player)
{
	if (pos != '1' && pos != '0' && pos != player)
		ft_exit("Wrong fill of map");
}

void	ft_empty(char *line)
{
	if (!*line)
		ft_exit("File is empty");
}

int	ft_check_path_color(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (0);
		++line;
	}
	return (1);
}

int	ft_check_lines(t_game *game)
{
	
}