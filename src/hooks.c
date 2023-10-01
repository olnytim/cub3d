/* ************************************************************************** */
/*                                                                            */
/*                                                    *._           _.*   @   */
/*   hooks.c                                            |\  \\_//  /|     #   */
/*                                                      \/         \/     $   */
/*   By: olnytim <yearagotomorrow@gmail.com>           _|_    V  V  |_    %   */
/*                                                  *=.    =  _*  =   .=* ^   */
/*   Created: 2023/10/02 02:37:22 by olnytim           \= ___________=/   &   */
/*   Updated: 2023/10/02 02:37:24 by olnytim                /     \       *   */
/*                                                                            */
/* ************************************************************************** */

#include "../hf/cub3d.h"

int	ft_hook(int keycode, t_game *game)
{
	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		ft_endgame(game);
	// if (keycode == W)
	// 	;
	// if (keycode == S)
	// 	;
	// if (keycode == D)
	// 	;
	// if (keycode == A)
	// 	;
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_game *game)
{
	(void)game;
	mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
	printf("keycode: %d\n", button);
	printf("Mouse position: X = %d, Y = %d\n", x, y);
	return (0);
}
