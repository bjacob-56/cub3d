#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include  "mlx.h"
#include "ft_cub3d.h"

// clang ft_cub3d.c -L. -lmlx && ./a.out



//	mlx_pixel_put ( mlx_ptr, win_ptr, size_x / 2, size_y / 2, color);
//	mlx_string_put ( mlx_ptr, win_ptr, size_x / 2, size_y / 2, color, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");


t_image	ft_print_img_middle(void *mlx_ptr, t_window t_win, char *img_path)
{
	t_image	t_img;
	int		start_x_img;
	int		start_y_img;

	t_img.x_i = 800;
	t_img.y_i = 800;

//	t_img.image = mlx_xpm_file_to_image(mlx_ptr, img_path, &t_img.x_i, &t_img.y_i);
	t_img.image = mlx_xpm_file_to_image(mlx_ptr, img_path, &t_img.x_i, &t_img.y_i);

	printf("x_img = %d, y_img = %d\n", t_img.x_i, t_img.x_i);

	start_x_img = 0;
	start_y_img = (t_win.y_w - t_img.y_i) / 2;

	while (start_x_img < t_win.x_w)
	{
		mlx_put_image_to_window( mlx_ptr, t_win.window, t_img.image, start_x_img, start_y_img);
		start_x_img += t_img.x_i;
	}
	return (t_img);
}

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

void	ft_open_minilibx(void)
{
	void	*mlx_ptr;
	t_window	t_win;
	char	*window_title = "Fenetre_1";
	int		color_floor;
	int		color_ceiling;
	t_image		t_img;

//	char	*img_path = "../images/mur_N.xpm";
	char	*img_path = "../images/image_N_2.xpm";

	mlx_ptr = mlx_init();

	t_win.x_w = 1920;
	t_win.y_w = 1080;
	t_win.window = mlx_new_window(mlx_ptr, t_win.x_w, t_win.y_w, window_title);

	t_img = ft_print_img_middle(mlx_ptr, t_win, img_path);

	color_floor = 0x00ABCDEF;
	color_ceiling = 0x0000FF00;
	ft_print_ceiling(mlx_ptr, t_win, color_ceiling, t_img);
	ft_print_floor(mlx_ptr, t_win, color_floor, t_img);

/////////////
int pixel_bits;
int line_bytes;
int endian;
char *buffer = mlx_get_data_addr(t_img.image, &pixel_bits, &line_bytes, &endian);

printf("pix = %d\nline = %d\nendian = %d\nbuffer = %s\n", pixel_bits, line_bytes, endian, buffer);
//////////////////
	



	while (mlx_loop(mlx_ptr))
{
	





}
//	mlx_clear_win_ptr(mlx_ptr, win_ptr);
}




int main()
{
	ft_open_minilibx();
//	while (1);
}