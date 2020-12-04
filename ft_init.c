#include "ft_cub3d.h"

t_window	open_window(void *mlx_ptr, int width, int height, char *title)
{
	t_window	t_win;

	t_win.title = title;
	t_win.x_w = width;
	t_win.y_w = height;
	t_win.window = mlx_new_window(mlx_ptr, t_win.x_w, t_win.y_w, t_win.title); // check si ca a marché ?
	return (t_win);
}

t_image		open_image(void *mlx_ptr, char *img_path, int width, int height)
{
	t_image	t_img;
	int		p;
	int		e;

	if (!width)
		t_img.x_i = width;
	if (!height)
		t_img.y_i = height;
	t_img.image = mlx_xpm_file_to_image(mlx_ptr, img_path, &t_img.x_i, &t_img.y_i); // check si ca a marché ?	
	t_img.p_color = (int*)mlx_get_data_addr(t_img.image, &p, &t_img.line_bytes, &e);
	return (t_img);
}