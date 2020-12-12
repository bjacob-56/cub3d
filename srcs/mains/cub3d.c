/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 10:15:21 by bjacob           ###   ########lyon.fr   */
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

int	ft_display_image(t_game *g, t_session t_ses,
		t_window t_win, t_player player)
{
	t_ray		ray;
	t_vector	p_square;
//	int			p;
	int			e;

	mlx_destroy_image(g->session.id, g->img.image);
	if (!(g->img.image = mlx_new_image(t_ses.id, t_win.x_w, t_win.y_w)))
		return (-1);
	g->img.p_color = (int*)mlx_get_data_addr(g->img.image, &g->img.bpp,
					&g->img.line_bytes, &e);	
	ray.x = 0;
	while (ray.x < t_win.x_w)
	{
		set_ray_dir_and_delta(t_win, player, &ray);
		get_step_and_side_dist(player, &ray);
		ray.side = find_closest_wall(t_win, player, &p_square, &ray);
		ray.dist_wall = get_dist_wall(player, ray, p_square);
		t_win.z_dist[ray.x] = ray.dist_wall;
		vertical_line_to_image(*g, ray);
		ray.x++;
	}
	g->img = ft_display_stripes(t_ses, t_win, player, g->img);
	mlx_put_image_to_window(t_ses.id, t_win.window, g->img.image, 0, 0);
	return (1);
}

int		ft_cub3d(int save, char *map_path)
{
	t_game		game;
//	double		time;
//	double		oldTime;

	dprintf(1, "save = %d\nmap_path = %s\n", save, map_path);

	game.session = init_session();
	if (init_window(&game, map_path, "Cube3d") == -1)
	{
		dprintf(1, "Error init\n"); // a corriger
		return (free_all_ptr(&game));
	}
	game.player = init_player(game.window);
	if (!(game.window.window = mlx_new_window(game.session.id, game.window.x_w,
					game.window.y_w, game.window.title)))
		return (free_all_ptr(&game));
	if (!(game.img.image = mlx_new_image(game.session.id, game.window.x_w,
									game.window.y_w)))
		return (free_all_ptr(&game));
	if (ft_display_image(&game, game.session, game.window, game.player) == -1)
		return (free_all_ptr(&game));
	if (save)
		save_image("start_image.bmp", game, game.window.x_w * game.window.y_w);


	mlx_hook(game.window.window, 17, 0, ft_clean_prog, &game);
	mlx_hook(game.window.window, 2, 0, &ft_key_press, &game);
	mlx_hook(game.window.window, 3, 0, &ft_key_release, &game);
	mlx_loop_hook(game.session.id, &ft_move_player, &game);
	mlx_loop(game.session.id);
	return (0);	

}

int		main(int argc, char **argv)
{
	char *map_path;

	if (argc < 2 || argc > 3)
		return (-1); // erreur a gerer
	else if (argc == 2)
		ft_cub3d(0, argv[1]);
	else
	{
		if (!ft_strncmp("--save", argv[1], 7))
			ft_cub3d(1, argv[2]);
		else
			return (-1); // erreur a gerer
	}
	return (0);
}
