#include "ft_cub3d.h"

t_session	init_session(void)
{
	t_session	session;

	session.id = mlx_init();
	session.images.no = open_image(session.id, "./images/mur_N.xpm", 0, 0);
	session.images.so = open_image(session.id, "./images/mur_S.xpm", 0, 0);
	session.images.ea = open_image(session.id, "./images/mur_E.xpm", 0, 0);
	session.images.we = open_image(session.id, "./images/mur_W.xpm", 0, 0);
	session.images.sprite = open_image(session.id, "./images/mur_W.xpm", 0, 0); // A CHANGER
	return (session);
}

t_window	init_window(t_session t_ses, char *map_file_path, char *title)
{
	t_window	t_win;
	int			fd;
	int			nb_read;
	int			res_x;
	int			res_y;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		return (fd);
	nb_read = set_data_map_info(fd, &t_win.map_info);
	if (nb_read == -1)
	{
		free_map_info_data(&t_win.map_info);
		return (NULL); // 							reponse a gerer
	}
	res_x = t_win.map_info.resolution_x;
	res_y = t_win.map_info.resolution_y;

	if (parse_map(&t_win, map_file_path, fd, nb_read) == -1 ||
		check_map_with_propagation(t_win) == -1)
		return (NULL);

	t_win = open_window(t_ses.id, res_x, res_y, title); // a mettre ailleurs

	return (t_win);
}

t_player	init_player(t_window t_win)
{
	t_player	player;

	if (t_win.map_info.start.direction == 'N')
		player.dir_x = 0;
		player.dir_y = FOV * -1;
	if (t_win.map_info.start.direction == 'S')
		player.dir_x = 0;
		player.dir_y = FOV * 1;
	if (t_win.map_info.start.direction == 'E')
		player.dir_x = FOV * 1;
		player.dir_y = 0;
	if (t_win.map_info.start.direction == 'W')
		player.dir_x = FOV * -1;
		player.dir_y = 0;
	player.plane_x = player.dir_y;
	player.plane_y = -1 * player.dir_x;
	player.pos_x = t_win.map_info.start.column;
	player.pos_y = t_win.map_info.start.line;
//	player.pos_x = 1.5;
//	player.pos_y = 1.5;
	player.p_square_x = floor(player.pos_x);
	player.p_square_y = floor(player.pos_y);
	return (player);
}

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
	int		*img_c;

	if (!width)
		t_img.x_i = width;
	if (!height)
		t_img.y_i = height;
	t_img.image = mlx_xpm_file_to_image(mlx_ptr, img_path, &t_img.x_i, &t_img.y_i); // check si ca a marché ?	
	img_c = (int*)mlx_get_data_addr(t_img.image, &p, &t_img.line_bytes, &e);
	t_img.p_color = img_c;
	return (t_img);
}
