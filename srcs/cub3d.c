/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 11:25:07 by bjacob           ###   ########lyon.fr   */
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

//dprintf(1, "\n\n-------------------------------------------------------\n");

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
		t_win.z_dist[ray.x] = ray.dist_wall;

// tracé de la ligne verticale du mur
		vertical_line_to_image(t_ses, t_win, t_img, player, ray); // a creer
//		draw_wall_vertical_line(t_ses, t_win, player, ray);
//	dprintf(1, "ray.x = %d\n", ray.x);
		ray.x++;
	}

	t_img = ft_display_stripes(t_ses, t_win, player, t_img, ray);

//dprintf(1, "nb_sprite = %d\n", t_win.map_info.nb_sprites);
//dprintf(1, "sprite_bites = %d\n", t_ses.images.sprite.line_bytes);


	mlx_put_image_to_window (t_ses.id, t_win.window, t_img.image, 0, 0);
}








void	ft_put_stripe_line_to_image(t_window t_win,
		t_image t_img_src, t_pixel_info *pix, t_image t_img_new)
{
	int		y_off;
	double	y_step;
	int		i;
	int		color;

//	pix->x_img = ft_min(pix->x_img, t_img.x_i - 1); // a voir si -1 ou non // vraiment nécessaire ?
	pix->y_img = 0;
	y_step = (double)t_img_src.y_i / (double)pix->line_height;
//	pix->y_coord = ft_max((t_win.y_w - pix->line_height) / 2, 0);
	y_off = ft_max(y_step * (pix->line_height - t_win.y_w) / 2, 0);
	i = 0;
	while (i < pix->line_height && pix->y_coord < t_win.y_w) // a ajuster ?
	{
		pix->y_img = (int)(i * y_step + y_off);
		color = t_img_src.p_color[pix->x_img + t_img_src.line_bytes * pix->y_img / 4];
		t_img_new.p_color[pix->x_coord + t_win.x_w * pix->y_coord] = color; // pas sur
//		mlx_pixel_put(mlx_ptr, t_win.window, pix->x_coord, pix->y_coord, color);
		i++;
		pix->y_coord++;
	}
}



t_image	ft_display_stripes(t_session t_ses, t_window t_win, t_player player, t_image t_img, t_ray ray)
{
	int	i;
	t_image	t_img_s;

	t_img_s = t_ses.images.sprite;
	i = 0;
	sort_sprites(t_win.map_info.sprites, t_win.map_info.nb_sprites, player);
	while (i < t_win.map_info.nb_sprites)
	{
		double	spriteX;
		double	spriteY;
		double	invD;
		double	transX;
		double	transY;

		spriteX = t_win.map_info.sprites[i].x - player.pos_x;
		spriteY = t_win.map_info.sprites[i].y - player.pos_y;
		invD = 1.0 / (player.plane_x * player.dir_y - player.plane_y * player.dir_x);
		transX = invD * (player.dir_y * spriteX - player.dir_x * spriteY);
		transY = invD * (player.plane_x * spriteY - player.plane_y * spriteX);

		int	sprite_screenX = (int)(t_win.x_w * (1 + transX / transY));

		int	sprite_height = abs((int)(t_win.y_w / transY));
		int	sprite_width = abs((int)(t_win.y_w / transY));

		int	drawStartY = ft_max((t_win.y_w - sprite_height) / 2, 0);
		int	drawEndY = ft_min((t_win.y_w + sprite_height) / 2, t_win.y_w - 1);
		int	drawStartX = (sprite_screenX - sprite_width) / 2;
		int	drawEndX = ft_min((sprite_screenX + sprite_width) / 2, t_win.x_w - 1);

		int j;
		j = drawStartX;

		while (j < drawEndX)
		{
			int texX = (int)(256 * (j - drawStartX) * t_img_s.x_i / sprite_width) / 256;
			int y;
			y = drawStartY;
			if (transY > 0 && j > 0 && j < t_win.x_w && transY < t_win.z_dist[j])
			{
				while (y < drawEndY)
				{
					int	d;
					d = (y - (t_win.y_w - sprite_height) / 2) * 256;
					int texY;
					texY = ((d * t_img_s.y_i) / sprite_height) / 256;
					int color;
					color = t_img_s.p_color[t_img_s.line_bytes * texY / 4 + texX];
					if (color)
						t_img.p_color[j + t_img.line_bytes * y / 4] = color;
					y++;
				}
			}
			j++;
		}
		i++;
	}

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
