#include "ft_cub3d.h"

// ------------------------------------

int	**init_map(int x, int y)
{
	int **map;
	int i;
	int j;

	i = 0;
	map = malloc (sizeof(int*) * y);
	while(i < y)
		map[i++] = malloc(sizeof(int) * x);

	i = 0;
	j = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
			map[i][j++] = 1;
		i++;
	}
	i = 1;
	j = 1;
		while (i < y - 1)
	{
		j = 1;
		while (j < x - 1)
			map[i][j++] = 0;
		i++;
	}

	map[2][2] = 1;

	i = 0;
	j = 0;
	while (i < 5)
	{
		j = -1;
		while (++j < 5)
			printf("%d", map[i][j]);
		printf("\n");
		i++;
	}

	return (map);
}
// ------------------------------------


t_session	init_session(void)
{
	t_session	session;

	session.id = mlx_init();
	session.images.no = open_image(session.id, "./images/mur_N.xpm", 0, 0);
	session.images.so = open_image(session.id, "./images/mur_S.xpm", 0, 0);
	session.images.ea = open_image(session.id, "./images/mur_E.xpm", 0, 0);
	session.images.we = open_image(session.id, "./images/mur_W.xpm", 0, 0);
	return (session);
}

t_window	init_window(t_session t_ses) // arguments a ajouter
{
	t_window	t_win;

	t_win = open_window(t_ses.id, 1920, 1080, "Fenetre_1");
	t_win.map = init_map(5, 5);
	t_win.map[3][3] = 1;
	return (t_win);
}

t_player	init_player(void) // arguments a ajouter
{
	t_player	player;

	player.dir_x = 0.5;
	player.dir_y = 0.5;

	player.plane_x = player.dir_y;
	player.plane_y = -1 * player.dir_x;

	player.pos_x = 1.5;
	player.pos_y = 1.5;

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
