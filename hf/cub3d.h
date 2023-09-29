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
# include <mlx.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>


// set the sizes of map and screen
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

// define structs
typedef struct s_map
{
	int		**lines;
	int		fd;
	int		raws_count;
	int		map_size;
	char	*address;
	char	**map;
	char	*line;
	char	dir;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*c_color;
	char	*f_color;
}	t_map;

typedef struct s_player
{
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	t_player	*player;
	t_map		*map;
	void		*mlx;
	void		*win;
	int			ceiling_color;
	int			floor_color;
}	t_game;

// linux keys is the same as ascii
enum {
	W = 119,
	S = 115,
	D = 100,
	A = 97,
	ESC = 65307
};

// list of functions
/* exit functions */
void	ft_exit(char *str);
void	malloc_err(int condition, char *str);
int		ft_endgame(t_game *game);

/* parse functions */
void	ft_empty(char *line);
char	*ft_skip_spaces(char *line);
void	ft_path_parse(t_game *game);
void	ft_print_info(t_game *game);
void	ft_parse(t_game *game, int ac, char **av);
void	ft_sizes(t_game *game, int ac, char **av);
void	ft_map_parse(t_game *game, char *line);
void	ft_check_fence(t_game *game, int x, int y);
void	ft_convert_colors(t_game *game);

int		ft_check_path_color(char *line);

#endif
