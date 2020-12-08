#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ft_cub3d.h"

// clang ft_tests_cub3d.c -L./minilibx_mms_20200219 -lmlx && ./a.out



void	ft_print_ceiling(void *mlx_ptr, t_window t_win, int color, t_image t_img)
{
	int	x;
	int	y;

	y = 0;
	while (y < (t_win.y_w - t_img.y_i) / 2)
	{
		x = 0;
		while (x < t_win.x_w)
			mlx_pixel_put (mlx_ptr, t_win.window, x++, y, color);
		y++;
	}
}

void	ft_print_floor(void *mlx_ptr, t_window t_win, int color, t_image t_img)
{
	int	x;
	int	y;

	y = (t_win.y_w + t_img.y_i) / 2;
	while (y < t_win.y_w)
	{
		x = 0;
		while (x < t_win.x_w)
			mlx_pixel_put (mlx_ptr, t_win.window, x++, y, color);
		y++;
	}
}
