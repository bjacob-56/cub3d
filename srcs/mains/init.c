/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 11:20:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 13:19:52 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_session	init_session(void)
{
	t_session	session;

	session.id = mlx_init();
	session.images.no = open_image(session.id, "./images/mur_N.xpm", 0, 0);
	session.images.so = open_image(session.id, "./images/mur_S.xpm", 0, 0);
	session.images.ea = open_image(session.id, "./images/mur_E.xpm", 0, 0);
	session.images.we = open_image(session.id, "./images/mur_W.xpm", 0, 0);
	session.images.sprite = open_image(session.id,
										"./images/column.xpm", 0, 0); // A CHANGER
	return (session);
}

/*
t_window	window_null(void) // A AJUSTER ?
{
	t_window t_win;

	t_win.window = NULL;
	return (t_win);
}
*/

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
	if ((g->window.x_w = ft_min(g->window.map_info.resolution_x, X_RES_SCREEN))
		<= 0 ||	(g->window.y_w = ft_min(g->window.map_info.resolution_y,
		Y_RES_SCREEN)) <= 0)
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
	t_img.image = mlx_xpm_file_to_image(mlx_ptr, img_path,
					&t_img.x_i, &t_img.y_i); // check si ca a marché ?	
	img_c = (int*)mlx_get_data_addr(t_img.image, &p, &t_img.line_bytes, &e);
	t_img.p_color = img_c;
	return (t_img);
}
