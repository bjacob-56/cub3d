#ifndef FT_CUB3D_H
# define FT_CUB3D_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include  "./minilibx_mms_20200219/mlx.h"

typedef struct	s_window
{
	void	*window;
	int		x_w;
	int		y_w;
	char	*title;
}				t_window;

typedef struct	s_image
{
	void	*image;
	int		x_i;
	int		y_i;
	int		line_bytes;
	int		*p_color;
}				t_image;

typedef struct	s_player
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_player;

typedef	struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_img_poles
{
	t_image	no;
	t_image	so;
	t_image	ea;
	t_image	we;
}				t_img_poles;

// ft_cub3d.c


// ft_init.c
t_window	open_window(void *mlx_ptr, int width, int height, char *title);
t_image		open_image(void *mlx_ptr, char *img_path, int width, int height);


// ft_draw.c
void	ft_draw_line_image(void *mlx_ptr, t_window t_win, t_image t_img, int x_text, int x_coord, int line_height);
void	ft_print_image_bis(void *mlx_ptr, t_window t_win, t_image t_img);


// ft_maths.c
int	ft_max(int a, int b);
int	ft_min(int a, int b);

#endif