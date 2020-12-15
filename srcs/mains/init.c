/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 11:20:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/13 15:11:00 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void		init_session_images_and_ptrs(t_game *game)
{
	game->img.image = NULL;
	game->session.images.no.image = NULL;
	game->session.images.so.image = NULL;
	game->session.images.ea.image = NULL;
	game->session.images.we.image = NULL;
	game->session.images.sprite.image = NULL;
	game->ptrs = NULL;
	game->window.window = NULL;
	game->error = 1;
}

int			init_session(t_game *game)
{
	game->session.id = mlx_init();
	game->session.images.no = open_image(game->session.id,
									game->window.map_info.path_no, 0, 0);
	if (!game->session.images.no.image)
		return (-12);
	game->session.images.so = open_image(game->session.id,
									game->window.map_info.path_so, 0, 0);
	if (!game->session.images.so.image)
		return (-12);
	game->session.images.ea = open_image(game->session.id,
									game->window.map_info.path_ea, 0, 0);
	if (!game->session.images.ea.image)
		return (-12);
	game->session.images.we = open_image(game->session.id,
									game->window.map_info.path_we, 0, 0);
	if (!game->session.images.we.image)
		return (-12);
	game->session.images.sprite = open_image(game->session.id,
									game->window.map_info.path_sprite, 0, 0);
	if (!game->session.images.sprite.image)
		return (-12);
	return (1);
}

int			init_window(t_game *g, char *map_file_path, char *title)
{
	int			fd;
	int			nb_read;
	int			res_x;
	int			res_y;
	int			err;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		return (-6);
	nb_read = set_data_map_info(fd, g, 0, 0);
	if (nb_read < 0)
		return (nb_read);
	res_x = g->window.map_info.resolution_x;
	res_y = g->window.map_info.resolution_y;
	if ((err = parse_map(g, map_file_path, fd, nb_read)) < 0 ||
		(err = check_map_with_propagation(g, &g->window)) < 0)
		return (err);
	g->window.title = title;
	if ((g->window.x_w = ft_min(g->window.map_info.resolution_x, X_RES))
		<= 0 || (g->window.y_w = ft_min(g->window.map_info.resolution_y,
		Y_RES)) <= 0)
		return (-7);
	if (!(g->window.z_dist = malloc_lst(g, sizeof(double) * g->window.x_w)))
		return (-8);
	return (1);
}

t_player	init_player(t_window t_win)
{
	t_player	player;

	player.dir_x = 0;
	player.dir_y = 0;
	if (t_win.map_info.start.direction == 'N')
		player.dir_x = FOV * -1;
	if (t_win.map_info.start.direction == 'S')
		player.dir_x = FOV * 1;
	if (t_win.map_info.start.direction == 'E')
		player.dir_y = FOV * 1;
	if (t_win.map_info.start.direction == 'W')
		player.dir_y = FOV * -1;
	player.plane_x = player.dir_y;
	player.plane_y = -1 * player.dir_x;
	player.pos_x = t_win.map_info.start.column + 0.5;
	player.pos_y = t_win.map_info.start.line + 0.5;
	player.p_square_x = floor(player.pos_x);
	player.p_square_y = floor(player.pos_y);
	player.move.straight_pos = 0;
	player.move.straight_neg = 0;
	player.move.turn_left = 0;
	player.move.turn_right = 0;
	player.move.side_left = 0;
	player.move.side_right = 0;
	return (player);
}

t_image		open_image(void *mlx_ptr, char *img_path, int width, int height)
{
	t_image	t_img;
	int		p;
	int		e;
	int		*img_c;

	if (!width)
		t_img.x_i = width;
	if (!height)
		t_img.y_i = height;
	if (!(t_img.image = mlx_xpm_file_to_image(mlx_ptr, img_path,
					&t_img.x_i, &t_img.y_i)))
		return (t_img);
	img_c = (int*)mlx_get_data_addr(t_img.image, &p, &t_img.line_bytes, &e);
	t_img.p_color = img_c;
	return (t_img);
}
