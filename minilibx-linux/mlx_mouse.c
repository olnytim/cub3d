#include "mlx_int.h"

int		mlx_mouse_move(t_xvar *xvar, t_win_list *win, int x, int y)
{
	XWarpPointer(xvar->display, None, win->window, 0, 0, 0, 0, x, y);
	return (0);
}

int		mlx_mouse_hide(t_xvar *xvar, t_win_list *win)
{
	static char data[1] = {0};
	Cursor cursor;
	Pixmap blank;
	XColor dummy;

	blank = XCreateBitmapFromData(xvar->display, win->window, data, 1, 1);
	cursor = XCreatePixmapCursor(xvar->display, blank, blank, &dummy, &dummy, 0, 0);
	XDefineCursor(xvar->display, win->window, cursor);
	XFreePixmap(xvar->display, blank);
	XFreeCursor(xvar->display, cursor);
}

int		mlx_mouse_show(t_xvar *xvar, t_win_list *win)
{
	XUndefineCursor(xvar->display, win->window);
}

/*
** Queries the position of the mouse pointer relative to the origin of the
** specified window and saves it to the provided location.
**
** If the pointer is not on the same screen as the specified window, both
** win_x_return and win_y_return are set to zero and the function returns 0.
*/

int		mlx_mouse_get_pos(t_xvar *xvar, t_win_list *win, \
			int *win_x_return, int *win_y_return)
{
	Window		root_return;
	Window		child_return;
	int			root_x_return;
	int			root_y_return;
	unsigned	mask_return;

	return (XQueryPointer(xvar->display, win->window, \
		&root_return, &child_return, &root_x_return, &root_y_return, \
		win_x_return, win_y_return, &mask_return));
}

// int	mlx_mouse_get_pos(mlx_win_list_t *win, int *x, int *y)
// {
//   CGPoint	point;
//   id		thewin;
//   NSRect	pos;

//   thewin = [(id)(win->winid) win];
//   pos = [(id)(win->winid) frame];
//   point = [thewin mouseLocationOutsideOfEventStream];
//   *x = point.x;
//   *y = NSHeight(pos) - 1 - point.y;
//   return (0);
// }