/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/09 16:49:06 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_display_image(t_session t_ses, t_window t_win, t_player player)
{
	t_image		t_img;
	t_ray		ray;
	t_vector	p_square;
	int			p;
	int			e;

	t_img.image = mlx_new_image(t_ses.id, t_win.x_w, t_win.y_w);
	t_img.p_color = (int*)mlx_get_data_addr(t_img.image, &p, &t_img.line_bytes, &e);
	ray.x = 0;
	while (ray.x < t_win.x_w)
	{
// calcul de la direction du rayon
		set_ray_dir_and_delta(t_win, player, &ray);

// calcul des pas entre deux murs selon x et y
		get_step_and_side_dist(player, &ray);

// projection du rayon jusqu'au mur le plus proche
		ray.side = find_closest_wall(t_win, player, &p_square, &ray);

// calcul de la distance entre le player et le mur trouvé
		ray.dist_wall = get_dist_wall(player, ray, p_square);

// tracé de la ligne verticale du mur
		vertical_line_to_image(t_ses, t_win, t_img, player, ray); // a creer
//		draw_wall_vertical_line(t_ses, t_win, player, ray);
//	dprintf(1, "ray.x = %d\n", ray.x);

		t_img = ft_display_stripes(t_ses, t_win, player, t_img, ray);
		ray.x++;
	}
//dprintf(1, "aaaaaaaaa\n");

	mlx_put_image_to_window (t_ses.id, t_win.window, t_img.image, 0, 0);
}



t_image	ft_display_stripes(t_session t_ses, t_window t_win, t_player player, t_image t_img, t_ray ray)
{
//	t_image		t_img;
//	t_ray		ray;
	t_vector	p_square;
	int			p;
	int			e;

//	t_img.image = mlx_new_image(t_ses.id, t_win.x_w, t_win.y_w);
//	t_img.p_color = (int*)mlx_get_data_addr(t_img.image, &p, &t_img.line_bytes, &e);
// calcul de la direction du rayon
//		set_ray_dir_and_delta(t_win, player, &ray); // necessaire ?

// calcul des pas entre deux murs selon x et y
		get_step_and_side_dist(player, &ray);

// projection du rayon jusqu'au mur le plus proche
		ray.side = find_closest_sprite(t_win, player, &p_square, &ray);


//	double	spriteX = (p_square.x - player.pos_x + (1 - ray.step.x) / 2) / ray.dir.x;
//	double	spriteY = (p_square.y - player.pos_y + (1 - ray.step.y) / 2) / ray.dir.y;
	double	spriteX = (p_square.x - player.pos_x);
	double	spriteY = (p_square.y - player.pos_y);

	double	invD = 1.0 / (player.plane_x * player.dir_y - player.plane_y * player.dir_x);
	double	transX = invD * (player.dir_y * spriteX - player.dir_x * spriteY);
	double	transY = invD * (player.plane_x * spriteY - player.plane_y * spriteX);

//	ray.side_dist.x = transX;
//	ray.side_dist.y = transY;

//	if (!ray.side)
//		ray.dist_wall = transX; // a voir si suffisant pour texture
//	else
//		ray.dist_wall = transY;



// calcul de la distance entre le player et le mur trouvé
		ray.dist_wall = get_dist_wall(player, ray, p_square);

// tracé de la ligne verticale du mur
		if (t_win.map[(int)p_square.x][(int)p_square.y] == 2)
		{
			dprintf(1, "x = %d\n", ray.x);
			t_img = vertical_sprite_line_to_image(t_ses, t_win, t_img, player, ray); // a creer
		}
//		draw_wall_vertical_line(t_ses, t_win, player, ray);
	return (t_img);
}


int		main()
{
	t_game		game;
	t_session	t_ses;
	t_window	t_win;
	t_image		t_img;
	t_player	player;
	void		*param;

//	double		time;
//	double		oldTime;

	t_ses = init_session();
	t_win = init_window(t_ses, "map/map.cub", "Fenetre_1");
	player = init_player(t_win);

//	print_player_info(player); /////////////////

	if (!t_win.window)
		return (-1); // A AJUSTER/GERER

//	t_win.x_w = ft_min(t_win.map_info.resolution_x, X_RES_SCREEN);
//	t_win.y_w = ft_min(t_win.map_info.resolution_y, Y_RES_SCREEN);		
	t_win.window = mlx_new_window(t_ses.id, t_win.x_w, t_win.y_w, t_win.title); // check si ca a marché ?

	ft_display_image(t_ses, t_win, player);

//	free(t_win.map);
	game.session = t_ses;
	game.window = t_win;
	game.player = player;

	mlx_hook(t_win.window, 2, 0, &ft_key, &game);
	mlx_loop(t_ses.id);

	//	mlx_clear_win_ptr(mlx_ptr, win_ptr);

}
