/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 13:51:25 by bjacob           ###   ########lyon.fr   */
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
		set_ray_dir_and_delta(t_win, player, &ray);
		get_step_and_side_dist(player, &ray);
		ray.side = find_closest_wall(t_win, player, &p_square, &ray);
		ray.dist_wall = get_dist_wall(player, ray, p_square);
		t_win.z_dist[ray.x] = ray.dist_wall;
		vertical_line_to_image(t_ses, t_win, t_img, player, ray);
		ray.x++;
	}
	t_img = ft_display_stripes(t_ses, t_win, player, t_img);
	mlx_put_image_to_window (t_ses.id, t_win.window, t_img.image, 0, 0);
}

t_image	ft_display_stripes(t_session t_ses, t_window t_win,
		t_player player, t_image t_img)
{
	int	i;
	t_image	t_img_s;
	t_sprite_info	s_info;

	t_img_s = t_ses.images.sprite;
	i = 0;
	sort_sprites(t_win.map_info.sprites, t_win.map_info.nb_sprites, player);
	while (i < t_win.map_info.nb_sprites)
	{
		if (!(fabs(t_win.map_info.sprites[i].x - player.pos_x) < 0.02 &&
			fabs(t_win.map_info.sprites[i].y - player.pos_y) < 0.02))
		{
			s_info = get_sprite_info(t_win, player, i);
			ft_put_sprite_line_to_image(t_win, t_img, t_img_s, s_info);
		}
		i++;
	}
	return (t_img);
}

t_sprite_info	get_sprite_info(t_window t_win, t_player player, int i)
{
	t_sprite_info s_info;

	s_info.spritex = t_win.map_info.sprites[i].x - player.pos_x;
	s_info.spritey = t_win.map_info.sprites[i].y - player.pos_y;
	s_info.invD = 1.0 / (player.plane_x * player.dir_y -
						player.plane_y * player.dir_x);
	s_info.transf_x = s_info.invD * (player.dir_y * s_info.spritex -
						player.dir_x * s_info.spritey);
	s_info.transf_y = s_info.invD * (player.plane_x * s_info.spritey -
						player.plane_y * s_info.spritex);
	s_info.screen_x = (int)(t_win.x_w * (1 +
						s_info.transf_x / s_info.transf_y));
	s_info.height = abs((int)(t_win.y_w / s_info.transf_y));
	s_info.width = abs((int)(t_win.y_w / s_info.transf_y));
	s_info.draw_starty = ft_max((t_win.y_w - s_info.height) / 2, 0);
	s_info.draw_endy = ft_min((t_win.y_w + s_info.height) / 2, t_win.y_w - 1);
	s_info.draw_startx = (s_info.screen_x - s_info.width) / 2;
	s_info.draw_endx = ft_min((s_info.screen_x + s_info.width) / 2,
								t_win.x_w - 1);

	return (s_info);
}

int		get_sprite_color(t_image t_img_s, t_sprite_info s_info, int j, int d)
{
	int	color;
	int texX;
	int texY;

	texY = ((d * t_img_s.y_i) / s_info.height) / 256;
	texX = (int)(256 * (j - s_info.draw_startx) *
			t_img_s.x_i / s_info.width) / 256;
	color = t_img_s.p_color[t_img_s.line_bytes * texY / 4 + texX];
	return (color);
}

void	ft_put_sprite_line_to_image(t_window t_win, t_image t_img,
		t_image t_img_s, t_sprite_info s_info)
{
	int j;
	int	d;
	int y;
	int color;

	j = s_info.draw_startx - 1;
	while (++j < s_info.draw_endx)
	{
		y = s_info.draw_starty - 1;
		if (s_info.transf_y > 0 && j > 0 && j < t_win.x_w &&
			s_info.transf_y < t_win.z_dist[j])
		{
			while (++y < s_info.draw_endy)
			{
				d = (y - (t_win.y_w - s_info.height) / 2) * 256;
				color = get_sprite_color(t_img_s, s_info, j, d);
				if (color)
					t_img.p_color[j + t_img.line_bytes * y / 4] = color;
			}
		}
	}
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

//	print_player_info(player); /////////////////

	if (!t_win.window)
		return (-1); // A AJUSTER/GERER

//	t_win.x_w = ft_min(t_win.map_info.resolution_x, X_RES_SCREEN);
//	t_win.y_w = ft_min(t_win.map_info.resolution_y, Y_RES_SCREEN);		
	t_win.window = mlx_new_window(t_ses.id, t_win.x_w, t_win.y_w, t_win.title); // check si ca a marché ?

//	dprintf(1, "nb_sprites = %d\n", t_win.map_info.nb_sprites);

	ft_display_image(t_ses, t_win, player);

//	free(t_win.map);
	game.session = t_ses;
	game.window = t_win;
	game.player = player;

	mlx_hook(t_win.window, 2, 0, &ft_key, &game);
	mlx_loop(t_ses.id);

	//	mlx_clear_win_ptr(mlx_ptr, win_ptr);

}
