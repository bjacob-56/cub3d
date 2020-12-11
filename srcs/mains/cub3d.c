/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/11 11:58:34 by bjacob           ###   ########lyon.fr   */
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

t_image	ft_display_image(t_game game, t_session t_ses,
		t_window t_win, t_player player)
{
	t_image		t_img;
	t_ray		ray;
	t_vector	p_square;
	int			p;
	int			e;

	t_img.image = mlx_new_image(t_ses.id, t_win.x_w, t_win.y_w);
	t_img.p_color = (int*)mlx_get_data_addr(t_img.image, &p,
					&t_img.line_bytes, &e);
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
	mlx_put_image_to_window(t_ses.id, t_win.window, t_img.image, 0, 0);
	return (t_img);
}

int		main()
{
	t_game		game;
	void		*param;
	t_image		t_img;
//	double		time;
//	double		oldTime;

	game.session = init_session();
	if (init_window(&game, "map/map.cub", "Fenetre_1") == -1) // si erreur -> -1 ----> A GERER     prendre decision pour free_map_info_data
		return (-1);
	game.player = init_player(game.window);
	game.window.window = mlx_new_window(game.session.id, game.window.x_w,
					game.window.y_w, game.window.title); // check si ca a marché ?
	t_img = ft_display_image(game, game.session, game.window, game.player);



	// char *tab_bmp;
	// int	e;
	// int p;
	// tab_bmp = mlx_get_data_addr(t_img.image, &p,
	// 				&t_img.line_bytes, &e);
	// dprintf(1, "tab : %s\n", tab_bmp);
	// dprintf(1, "saved image = %d\n", save_image("./saved_image/image_test", tab_bmp));

//	free(game.window.map);

	mlx_hook(game.window.window, 17, 0, ft_clean_prog, &game);
	mlx_hook(game.window.window, 2, 0, &ft_key_press, &game);
	mlx_hook(game.window.window, 3, 0, &ft_key_release, &game);
	mlx_loop_hook(game.session.id, &ft_move_player, &game);
	mlx_loop(game.session.id);

	//	mlx_clear_win_ptr(mlx_ptr, win_ptr);
}
