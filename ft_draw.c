#include "ft_cub3d.h"





void	ft_draw_line_image(void *mlx_ptr, t_window t_win, t_image t_img, int x_text, int x_coord, int line_height)
{
	int		y;
	int		y0;
	int		y_off;
	double	y_step;
	int		i;
	int		color;

//	dprintf(1, "x = %d\n", x); /////////////////////////////////////////////////////////////////////

	x_text = ft_min(x_text, t_img.x_i - 1); // a voir si -1 ou non

	y = 0;
	y_step = (double)t_img.y_i / (double)line_height;

	if (t_win.y_w >= line_height)
	{
		i = 0;
		y0 = (t_win.y_w - line_height) / 2;
		y_off = 0;
	}
	else
	{
		i = 0;
		y0 = 0;
		y_off = y_step * (line_height - t_win.y_w) / 2; // a verifier
	}

	while (i < line_height && i + y0 < t_win.y_w) // a ajuster ?
	{
			y = (int)(i * y_step + y_off);
	// 	dprintf(1, "indice = %f\n", x + t_img.line_bytes * y / 4); /////////////////////////////////////////////////////////////////////
		color = t_img.p_color[x_text + t_img.line_bytes * y / 4];

		mlx_pixel_put(mlx_ptr, t_win.window, x_coord, i + y0, color);
		i++;
	}
}
