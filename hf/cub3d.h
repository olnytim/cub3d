/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:12:04 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/10 20:12:13 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// libs
# include "../libft/libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>

// set the sizes of map and screen
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

// define structs
typedef struct s_mapinfo
{
	int	height;
	int	width;
	int	*lines;
}	t_mapinfo;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	t_player	*player;
	t_mapinfo	*mapinfo;
}	t_game;

// list of functions
/* exit functions */
void	ft_exit(char *str);

/* parse functions */
void	ft_parse(int ac, char **av);
void	ft_sizes(int ac, char **av);

#endif
