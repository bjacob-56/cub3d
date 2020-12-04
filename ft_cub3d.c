#include "ft_cub3d.h"

/*

	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;

*/



void	ft_start(void *mlx_ptr, t_window t_win, int **map, t_player player)
{
//	t_player	player;
	double		time;
	double		oldTime;

	int nb_rays;
	int	x;

	t_img_poles	tab_img;
	t_image		t_img;

	t_vector	ray;
	t_vector	delta;
	t_vector	step;
	t_vector	side_dist;
	int			hit;
	int			side;
	int			mapX;
	int			mapY;
	double		dist_wall;

	tab_img.no = open_image(mlx_ptr, "./images/mur_N.xpm", 0, 0);
	tab_img.so = open_image(mlx_ptr, "./images/mur_S.xpm", 0, 0);
	tab_img.ea = open_image(mlx_ptr, "./images/mur_E.xpm", 0, 0);
	tab_img.we = open_image(mlx_ptr, "./images/mur_W.xpm", 0, 0);

	nb_rays = t_win.x_w;
//	nb_rays = 20;
	x = 0;

	while (x < nb_rays)
	{

//dprintf(1, "x = %d\n", x); /////////////////////////////////////////////////////////////////////


		ray.x = player.dirX + player.planeX * (2 * ((double)x / (double)nb_rays) - 1);
		ray.y = player.dirY + player.planeY * (2 * ((double)x / (double)nb_rays) - 1);
//dprintf(1, "ray.x = %f\n", ray.x); /////////////////////////////////////////////////////////////////////
//dprintf(1, "ray.y = %f\n", ray.y); /////////////////////////////////////////////////////////////////////

		if (ray.y == 0)
			delta.x = 0;
		else if (ray.x == 0)
			delta.x = 1;
		else
			delta.x = fabs(1 / ray.x);

		if (ray.x == 0)
			delta.y = 0;
		else if (ray.y == 0)
			delta.y = 1;
		else
			delta.y = fabs(1 / ray.y);

//dprintf(1, "delta.x = %f\n", delta.x); /////////////////////////////////////////////////////////////////////
//dprintf(1, "delta.y = %f\n", delta.y); /////////////////////////////////////////////////////////////////////


		mapX = (int)player.posX;
		mapY = (int)player.posY;



// calcul des pas entre deux murs selon x et y
		if (ray.x >= 0)
		{
			step.x = 1;
			side_dist.x = (1 - (player.posX - mapX)) * delta.x;
		}
		else
		{
			step.x = -1;
			side_dist.x = (player.posX - mapX) * delta.x;
		}
		if (ray.y >= 0)
		{
			step.y = 1;
			side_dist.y = (1 - (player.posY - mapY)) * delta.y;
		}
		else
		{
			step.y = -1;
			side_dist.y = (player.posY - mapY) * delta.y;
		}

//dprintf(1, "step.x = %f\n", step.x); /////////////////////////////////////////////////////////////////////
//dprintf(1, "step.y = %f\n", step.y); /////////////////////////////////////////////////////////////////////
//dprintf(1, "side_dist.x = %f\n", side_dist.x); /////////////////////////////////////////////////////////////////////
//dprintf(1, "side_dist.y = %f\n", side_dist.y); /////////////////////////////////////////////////////////////////////

// projection du rayon jusqu'au mur le plus proche
		hit = 0;
		while (!hit) // comment checker le mur le plus proche ?
		{	
			if (side_dist.x <= side_dist.y)
			{
				side_dist.x += delta.x;
				mapX += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta.y;
				mapY += step.y;
				side = 1;
			}
			if (map[mapX][mapY] > 0) // attention a ne pas depasser la limite
				hit = 1;
		}

// calcul de la distance entre le player et le mur trouvé
		if (!side)
			dist_wall = (mapX - player.posX + (1 - step.x) / 2) / ray.x; // a voir si suffisant pour texture
		else
			dist_wall = (mapY - player.posY + (1 - step.y) / 2) / ray.y;

// hauteur de la ligne a tracer
		int	line_height_std;
		int	line_height;

		line_height_std = 800; // a ajuster ?
		line_height = (int)(line_height_std / dist_wall);

// pixel ou commencer et terminer le tracage de la ligne
		int	pixel_start;
		int	pixel_end;

		pixel_start = ft_max((t_win.y_w - line_height) / 2, 0);
		pixel_end = ft_min((t_win.y_w + line_height) / 2, t_win.y_w - 1);

// calcul du x de la texture
		double	texture_x;
		int		texture_coord;

		if (!side)
			texture_x = player.posY + dist_wall * ray.y;
		else
			texture_x = player.posX + dist_wall * ray.x;
		texture_x -= floor(texture_x);

// dessin de la ligne verticale de la bonne texture
		
		if (!side)
		{
			if (step.x > 0)
				t_img = tab_img.ea;
			else
				t_img = tab_img.we;
		}
		else
		{
			if (step.y > 0)
				t_img = tab_img.no;
			else
				t_img = tab_img.so;
		}
		if ((!side && step.x > 0) || (side && step.y < 0)) // magie magie
			texture_x = 1 - texture_x;
		texture_coord = (int)(t_img.x_i * texture_x); 				// a voir s'il faut inverser si step < 0

if (x < 5)
{
	dprintf(1, "x = %d\nside = %d\n step.y = %f\nray.y = %f\n\n", x, side, step.y, ray.y);

}

		ft_draw_line_image(mlx_ptr, t_win, t_img, texture_coord, x, line_height);

		x++;
	}
}




// --------------------------------------------------

int	**init_map(void)
{
	int **map;
	int i;
	int j;

	i = 0;
	map = malloc (sizeof(int*) * 5);
	while(i < 5)
		map[i++] = malloc(sizeof(int) * 5);

	i = 0;
	j = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
			map[i][j++] = 1;
		i++;
	}
	i = 1;
	j = 1;
		while (i < 4)
	{
		j = 1;
		while (j < 4)
			map[i][j++] = 0;
		i++;
	}
/*

	i = 0;
	j = 0;
	while (i < 5)
	{
		j = -1;
		while (++j < 5)
			printf("map[%d][%d] = %d\n", i, j, map[i][j]);
		i++;
	}
*/
	return (map);
}

t_player	init_player(void)
{
	t_player	player;

	player.dirX = 0;
	player.dirY = 1;


	player.planeX = player.dirY;
	player.planeY = -1 * player.dirX;

	player.posX = 3;
	player.posY = 1.5;
	return (player);
}

//ray.y = player.dirY + player.planeY * (2 * ((double)x / (double)nb_rays) - 1);

int main()
{
	void		*mlx_ptr;
	t_window	t_win;
	t_image		t_img;
	t_player	player;
	int			**map;

	mlx_ptr = mlx_init();
	t_win = open_window(mlx_ptr, 1920, 1080, "Fenetre_1");
//	t_img = open_image(mlx_ptr, "./images/mur_E.xpm", 0, 0);

	map = init_map();
	player = init_player();

	ft_start(mlx_ptr, t_win, map, player);

free(map);

//	int x = 0;
//	int	line_height = 360;

/*
	while (x < t_img.x_i)
//	while (x < 100)
	{
		ft_draw_line_image(mlx_ptr, t_win, t_img, x, line_height);
		x++;
	}
*/
//	ft_print_image_bis(mlx_ptr, t_win, t_img);
//	mlx_put_image_to_window( mlx_ptr, t_win.window, t_img.image, 400, 0);
	
	while (mlx_loop(mlx_ptr));

	//	mlx_clear_win_ptr(mlx_ptr, win_ptr);

}
