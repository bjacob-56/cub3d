/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:24:14 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/06 12:40:36 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# include "./minilibx_mms_20200219/mlx.h"

# define LINE_HEIGHT_STD 800 // a ajuster ?

typedef struct	s_image
{
	void	*image;
	int		x_i;
	int		y_i;
	int		line_bytes;
	int		*p_color;
}				t_image;

typedef struct	s_img_poles
{
	t_image	no;
	t_image	so;
	t_image	ea;
	t_image	we;
}				t_img_poles;

typedef struct	s_session
{
	void		*id;
	t_img_poles	images;
}				t_session;

typedef struct	s_window
{
	void	*window;
	int		x_w;
	int		y_w;
	int		**map;
	char	*title;
}				t_window;

typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	p_square_x;
	double	p_square_y;
}				t_player;

typedef	struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_ray
{
	int			x;
	t_vector	dir;
	t_vector	step;
	t_vector	delta;
	t_vector	side_dist;
	int			side;
	double		dist_wall;
}				t_ray;

typedef struct	s_pixel_info
{
	int	x_coord;
	int	y_coord;
	int	x_img;
	int	y_img;
	int	line_height;
}				t_pixel_info;
/*
** ft_cub3d.c
*/

/*
** ft_init.c
*/
t_session		init_session(void);
t_window		init_window(t_session t_ses);
t_player		init_player(void);
t_window		open_window(void *mlx_ptr, int width, int height, char *title);
t_image			open_image(void *mlx_ptr, char *img_path,
				int width, int height);

/*
** ft_draw.c
*/
void			ft_draw_line_image(void *mlx_ptr, t_window t_win,
				t_image t_img, t_pixel_info pix);
void			ft_print_image_bis(void *mlx_ptr,
				t_window t_win, t_image t_img);

/*
** ft_ray_projection.c
*/
void			set_ray_dir_and_delta(t_window t_win,
				t_player player, t_ray *ray);
void			get_step_and_side_dist(t_player player, t_ray *ray);
int				find_closest_wall(t_window t_win, t_player player,
				t_vector *p_square, t_ray *ray);
double			get_dist_wall(t_player player, t_ray ray, t_vector p_square);

/*
** ft_display_image.c
*/
t_image			get_correct_wall(t_session t_ses, t_ray ray);
int				get_x_texture_coord(t_player player, t_ray ray, t_image t_img);
void			draw_wall_vertical_line(t_session t_ses, t_window t_win,
				t_player player, t_ray ray);

/*
** ft_maths.c
*/
int				ft_max(int a, int b);
int				ft_min(int a, int b);

#endif
