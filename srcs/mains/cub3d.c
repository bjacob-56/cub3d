/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 15:02:15 by bjacob           ###   ########lyon.fr   */
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

int	ft_display_image(t_game *g, t_window t_win, t_player player, int save)
{
	t_ray		ray;
	t_vector	p_square;
	int			e;

	mlx_destroy_image(g->session.id, g->img.image);
	if (!(g->img.image = mlx_new_image(g->session.id, t_win.x_w, t_win.y_w)))
		return (-2);
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
	g->img = ft_display_stripes(g->session, t_win, player, g->img);
	if (!save)
		mlx_put_image_to_window(g->session.id, t_win.window, g->img.image, 0, 0);
	return (1);
}

static void	launch_loop(t_game game)
{
//	double		time;
//	double		oldTime;

	mlx_hook(game.window.window, 17, 0, ft_clean_prog, &game);
	mlx_hook(game.window.window, 2, 0, &ft_key_press, &game);
	mlx_hook(game.window.window, 3, 0, &ft_key_release, &game);
	mlx_loop_hook(game.session.id, &ft_move_player, &game);
	mlx_loop(game.session.id);
}

int		ft_cub3d(int save, char *map_path)
{
	t_game		game;
	int			err;

	game.ptrs = NULL;
	if (check_map_extension(map_path) == -1)
		return (ft_error(-7, &game)); // a verifier
	game.session = init_session();
	if ((err = init_window(&game, map_path, "Cube3d")) < 0)		
		return (ft_error(err, &game));
	game.player = init_player(game.window);
	if (!(game.img.image = mlx_new_image(game.session.id, game.window.x_w,
									game.window.y_w)))
		return (ft_error(-2, &game));
	if (save)
		return (save_image("start_image.bmp", game)); // erreur a gerer ?
	if (!(game.window.window = mlx_new_window(game.session.id, game.window.x_w,
					game.window.y_w, game.window.title)))
		return (ft_error(-4, &game));
	if ((err = ft_display_image(&game, game.window, game.player, save)) < 0)
		return (ft_error(err, &game));
	launch_loop(game);
	return (0);
}

int		main(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
		return (ft_main_error()); // erreur a gerer
	else if (argc == 2)
		ft_cub3d(0, argv[1]);
	else
	{
		if (!ft_strncmp("--save", argv[1], 7))
			ft_cub3d(1, argv[2]);
		else
			return (ft_main_error()); // erreur a gerer
	}
	return (0);
}
