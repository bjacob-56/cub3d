/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 14:17:55 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Etapes :
**		- calcul de la direction du rayon
**		- calcul des pas entre deux murs selon x et y
**		- projection du rayon jusqu'au mur le plus proche
**		- calcul de la distance entre le player et le mur trouvé
**		- tracé de la ligne verticale du mur
*/

void	ft_display_image(t_game game, t_session t_ses, t_window t_win, t_player player)
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
		set_ray_dir_and_delta(t_win, player, &ray);
		get_step_and_side_dist(player, &ray);
		ray.side = find_closest_wall(t_win, player, &p_square, &ray);
		ray.dist_wall = get_dist_wall(player, ray, p_square);
		t_win.z_dist[ray.x] = ray.dist_wall;
		vertical_line_to_image(game, t_img, ray);
		ray.x++;
	}
	t_img = ft_display_stripes(t_ses, t_win, player, t_img);
	mlx_put_image_to_window (t_ses.id, t_win.window, t_img.image, 0, 0);
}




int		main()
{
	t_game		game;
//	t_session	t_ses;
	t_window	t_win;
	t_image		t_img;
//	t_player	player;
	void		*param;

//	double		time;
//	double		oldTime;

	game.session = init_session();
	game.window = init_window(game.session, "map/map2.cub", "Fenetre_1");
	game.player = init_player(game.window);

//	print_player_info(player); /////////////////

	if (!game.window.window)
		return (-1); // A AJUSTER/GERER

//	t_win.x_w = ft_min(t_win.map_info.resolution_x, X_RES_SCREEN);
//	t_win.y_w = ft_min(t_win.map_info.resolution_y, Y_RES_SCREEN);		
	game.window.window = mlx_new_window(game.session.id, game.window.x_w,
					game.window.y_w, game.window.title); // check si ca a marché ?

//	dprintf(1, "nb_sprites = %d\n", t_win.map_info.nb_sprites);

	ft_display_image(game, game.session, game.window, game.player);

//	free(game.window.map);

	mlx_hook(game.window.window, 2, 0, &ft_key, &game);
	mlx_loop(game.session.id);

	//	mlx_clear_win_ptr(mlx_ptr, win_ptr);

}
