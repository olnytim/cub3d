/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:12:04 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/09/19 16:33:59 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// libs
// # include <mlx.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
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
	int		**lines;
	int		fd;
	int		height;
	int		width;
	char	**map;
	char	*line;
	char	dir;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*c_color;
	char	*f_color;
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
void	ft_empty(char *line);
void	ft_check_end(t_game *game);
char	*ft_skip_spaces(char *line);
void	ft_path_parse(t_game *game);
void	ft_print_info(t_game *game);
void	check_position(char pos, char play1er);
void	ft_parse(t_game *game, int ac, char **av);
void	ft_sizes(t_game *game, int ac, char **av);
void	ft_map_parse(t_game *game, char *line);

int		ft_check_path_color(char *line);

#endif
