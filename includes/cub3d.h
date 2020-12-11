/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:24:14 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/11 16:29:15 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"

# include "../minilibx_mms_20200219/mlx.h"

# define HEIGHT_FACTOR 1.3 // a ajuster ?

# define FOV 0.66 // a verifier
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define ESC 53

# define THETA 0.07
# define ONE_STEP 0.2

# define X_RES_SCREEN 2560
# define Y_RES_SCREEN 1440

typedef struct	s_move
{
	int	straight_pos;
	int	straight_neg;
	int	turn_left;
	int	turn_right;
	int	side_left;
	int	side_right;
}				t_move;

typedef struct	s_sprite
{
	double	x;
	double	y;
}				t_sprite;

typedef struct s_sprite_info
{
	int		draw_startx;
	int		draw_endx;
	int		draw_starty;
	int		draw_endy;
	int		width;
	int		height;
	double	transf_x;
	double	transf_y;
	double	spritex;
	double	spritey;
	double	inv_d;
	int		screen_x;
}				t_sprite_info;


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
	t_image	sprite;
}				t_img_poles;

typedef struct	s_start
{
	char	direction;
	int		line;
	int		column;
}				t_start;

typedef struct	s_map_info
{
	int		resolution_x;
	int		resolution_y;
	char	*path_no;
	char	*path_so;
	char	*path_ea;
	char	*path_we;
	char	*path_sprite;
	int		f_colors[3];
	int		c_colors[3];
	int		nb_lines;
	int		nb_columns;
	int		nb_sprites;
	t_sprite	*sprites;
	t_start	start;
	int		is_valid;
}				t_map_info;

typedef struct	s_session
{
	void		*id;
	t_img_poles	images;
}				t_session;

typedef struct	s_window
{
	void		*window;
	int			x_w;
	int			y_w;
	int			**map;
	char		*title;
	t_map_info	map_info;
	double		*z_dist;
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
	t_move	move;
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

typedef struct s_game
{
	t_session	session;
	t_window	window;
	t_player	player;
	t_list		*ptrs;
	t_image		img;
}				t_game;

/*
** -----------------------------     MAINS     ----------------------------- **
*/

/*
** ft_cub3d.c
*/
int		ft_display_image(t_game *g, t_session t_ses, t_window t_win, t_player player);

/*
** ft_init.c
*/
t_session	init_session(void);
t_window	window_null(void); // A UTILISER ?
int			init_window(t_game *game, char *map_file_path, char *title);
t_player	init_player(t_window t_win);
t_image		open_image(void *mlx_ptr, char *img_path,
			int width, int height);

/*
** clear_objects.c
*/
void	*malloc_lst(t_game *game, int size);
int		malloc_trim_lst(t_game *game, char *s1, char c);
int		free_all_ptr(t_game *game);
int		free_line(char **line);

/*
** -----------------------------     MAP     ----------------------------- **
*/

/*
** ft_get_map_info.c
*/
int	get_map_resolution(t_game *g, char *line_bis);
int			get_map_floor(t_map_info *map_info, char *line_bis);
int			get_map_ceiling(t_map_info *map_info, char *line_bis);
int			get_nb_lines_columns_sprites(t_window *t_win, int fd,
			int size, char **line);
int			ft_reopen(int fd, char *map_file_path);

/*
** ft_fill_map_info.c
*/
void		init_map_info(t_map_info *map_info);
int	get_images_path(t_game *g, char *line);
int	get_floor_ceiling_color(t_game *g, char *line);
int		fill_map_info(char *line, t_game *g);
int		set_data_map_info(int fd, t_game *g, int nb_read,
						int nb_param);

/*
** ft_parse_map.c
*/
int			**ft_malloc_tab_2d(t_game *game);
int			check_and_fill_cell_i_j(t_window *t_win, char *line, int i, int j);
int			fill_tab_map(t_game *g, int fd, int i, char **line);
int			parse_map(t_game *game, char *map_file_path,
			int fd, int nb_read);
void		set_start_map(t_window *t_win, int i, int j, char *line);

/*
** ft_check_map.c
*/
int		**copy_map_to_map_bis(t_game *game, t_window t_win);
void		check_next_point(t_window *t_win, int **map_bis, int i, int j);
int		check_map_with_propagation(t_game *game, t_window *t_win);
int		go_to_nb_read(int fd, char **line, int nb_read);


/*
** -----------------------------     RAY TRACING     ----------------------------- **
*/

/*
** ft_ray_projection.c
*/
void		set_ray_dir_and_delta(t_window t_win,
			t_player player, t_ray *ray);
void		get_step_and_side_dist(t_player player, t_ray *ray);
int			find_closest_wall(t_window t_win, t_player player,
			t_vector *p_square, t_ray *ray);
double		get_dist_wall(t_player player, t_ray ray, t_vector p_square);
int			get_x_texture_coord(t_player player, t_ray ray, t_image t_img);

/*
** ft_display_image.c
*/
t_image		get_correct_wall(t_session t_ses, t_ray ray);
void		vertical_line_to_image(t_game game, t_ray ray);
void		ft_put_line_to_image(t_window t_win,
			t_image t_img_src, t_pixel_info *pix, t_image t_img_new);
void		ft_put_ceiling_to_image(t_window t_win,
			t_image t_img_src, t_pixel_info *pix, t_image t_img_new);
void		ft_put_floor_to_image(t_window t_win,
			t_image t_img_src, t_pixel_info *pix, t_image t_img_new);

/*
** sprites_utils.c
*/
void			sort_sprites(t_sprite *tab, int nb_sprites, t_player p);
t_sprite_info	get_sprite_info(t_window t_win, t_player player, int i);
int				get_sprite_color(t_image t_img_s, t_sprite_info s_info, int j, int d);

/*
** sprites_display.c
*/
t_image			ft_display_stripes(t_session t_ses, t_window t_win,
				t_player player, t_image t_img);
void			ft_put_sprite_line_to_image(t_window t_win, t_image t_img,
				t_image t_img_s, t_sprite_info s_info);

/*
** -----------------------------     EVENTS     ----------------------------- **
*/

/*
** event_handler.c
*/
int		ft_key_press(int key, t_game *game);
int		ft_key_release(int key, t_game *game);
int		ft_move_player(t_game *game);
int		ft_clean_prog(t_game *game);

/*
** move.c
*/
int	move_player_straight(t_game *game, int signe);
int	move_player_side(t_game *game, int signe);
int	turn_player(t_game *game, int signe);

/*
** -----------------------------     SAVE IMAGE     ----------------------------- **
*/

/*
** save_image.c
*/
int	save_image(char *path, char *buffer);

/*
** -----------------------------     MATHS     ----------------------------- **
*/

/*
** ft_maths.c
*/
int			ft_max(int a, int b);
int			ft_min(int a, int b);


/////////////////////////////////////
void	print_map(t_window t_win, int **map);
void	print_map_info(t_map_info map_info);
void	print_player_info(t_player player);
/////////////////////////////////////

#endif
