/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/08 09:10:49 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_display_image(t_session t_ses, t_window t_win, t_player player)
{
	t_image		t_img;
	t_ray		ray;
	t_vector	p_square;

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
		draw_wall_vertical_line(t_ses, t_win, player, ray);
		ray.x++;
	}
}

int		main()
{
	t_session	t_ses;
	t_window	t_win;
	t_image		t_img;
	t_player	player;

//	double		time;
//	double		oldTime;

	t_ses = init_session();
	t_win = init_window(t_ses, "/map/map.cub", "Fenetre_1");
	player = init_player(t_win);

	ft_display_image(t_ses, t_win, player);

	free(t_win.map);
	
	while (mlx_loop(t_ses.id));

	//	mlx_clear_win_ptr(mlx_ptr, win_ptr);

}
