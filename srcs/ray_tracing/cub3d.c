/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/08 16:47:45 by bjacob           ###   ########lyon.fr   */
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
		ray.x++;
	}
	mlx_put_image_to_window (t_ses.id, t_win.window, t_img.image, 0, 0);
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
	t_win = init_window(t_ses, "map/map2.cub", "Fenetre_1");
	player = init_player(t_win);

	if (!t_win.window)
		return (-1); // A AJUSTER/GERER
		
	t_win.window = mlx_new_window(t_ses.id, t_win.map_info.resolution_x,
								t_win.map_info.resolution_y,
								t_win.title); // check si ca a marché ?

	print_player_info(player);

t_win.x_w = t_win.map_info.resolution_x;
t_win.y_w = t_win.map_info.resolution_y;

	ft_display_image(t_ses, t_win, player);

//	free(t_win.map);
	game.session = t_ses;
	game.window = t_win;
	game.player = player;

	mlx_hook(t_win.window, 2, 0, &ft_key, &game);
	mlx_loop(t_ses.id);

	//	mlx_clear_win_ptr(mlx_ptr, win_ptr);

}
