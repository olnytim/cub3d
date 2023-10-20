/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgalyaut <tgalyaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 20:12:04 by tgalyaut          #+#    #+#             */
/*   Updated: 2023/10/16 16:12:42 by tgalyaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// libs
// # include <mlx.h>
# include "../libft/libft.h"
# include "../minilibx-mac/mlx.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <math.h>

// set the sizes of map and screen
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

// define structs
typedef struct s_map
{
	int		raws_count;
	int		map_size;
	int		fd;
	char	**map;
	char	*address;
	char	*line;
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*c_color;
	char	*f_color;
	char	dir;
}	t_map;

typedef struct s_player
{
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_rays
{
	double	time;
	double	old_time;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	double	tex_pos;
	int		line_height;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		tex_x;
	int		tex_y;
	int		tex_height;
}	t_rays;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		b_p_p;
	int		line_length;
	int		endian;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		height;
	int		width;
}	t_img;

typedef struct s_game
{
	t_player	*player;
	t_map		*map;
	t_rays		*rays;
	void		*mlx;
	void		*win;
	int			ceiling_color;
	int			floor_color;
	t_img		*img;
	t_img		*n;
	t_img		*s;
	t_img		*e;
	t_img		*w;
	t_img		*wall_t;
}	t_game;

 enum {
 	W = 13,
 	S = 1,
 	D = 2,
 	A = 0,
 	ESC = 53,
 	LEFT = 123,
 	RIGHT = 124,
 	UP = 126,
 	DOWN = 125,
	W_L = 119,
	S_L = 115,
	D_L = 100,
	A_L = 97,
	ESC_L = 65307,
	LEFT_L = 65361,
	RIGHT_L = 65363,
	UP_L = 65362,
	DOWN_L = 65364
 } ;

// list of functions
/* exit functions */
void	ft_exit(char *str);
void	malloc_err(int condition, char *str);
void	ft_img_check(t_img *img);
int		ft_endgame(t_game *game);

/* parse functions */
char	*ft_skip_spaces(char *line);
void	ft_empty(char *line);
void	ft_path_parse(t_game *game);
void	ft_print_info(t_game *game);
void	ft_parse(t_game *game, int ac, char **av);
void	ft_sizes(t_game *game, int ac, char **av);
void	ft_map_parse(t_game *game, char *line);
void	ft_check_fence(t_game *game, int x, int y);
void	ft_convert_colors(t_game *game);
int		ft_check_path_color(char *line);

/* hooks */
int		ft_mouse_hook(int button, t_game *game);
int		ft_hook(int keycode, t_game *game);

/* raycasting */
void	ft_tex_rendering(t_game *game, t_rays *rays, t_img *img, int x);
void	ft_render_walls(t_game *game, t_rays *rays, t_img *img);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	ft_walls_side(t_game *game, t_rays *rays);
void	ft_dda(t_game *game, t_rays *rays);
void	ft_raycasting(t_game *game);

#endif
