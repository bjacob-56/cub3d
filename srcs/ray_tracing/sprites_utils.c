/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:47:33 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 17:56:42 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void		switch_dist(double *tab, int i, int j)
{
	double	temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

static void		switch_sprites(t_sprite *tab, int i, int j)
{
	t_sprite	temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void			sort_sprites(t_sprite *tab, int nb_sprites, t_player p)
{
	int		i;
	int		j;
	double	sprite_dist[nb_sprites];
	double	temp;

	i = -1;
	while (++i < nb_sprites)
		sprite_dist[i] = (p.pos_x - tab[i].x) * (p.pos_x - tab[i].x) +
						(p.pos_y - tab[i].y) * (p.pos_y - tab[i].y);
	i = 0;
	while (i < nb_sprites)
	{
		j = i + 1;
		while (j < nb_sprites)
		{
			if (sprite_dist[j] > sprite_dist[i])
			{
				switch_dist(sprite_dist, i, j);
				switch_sprites(tab, i, j);
			}
			j++;
		}
		i++;
	}
}

t_sprite_info	get_sprite_info(t_window t_win, t_player player, int i)
{
	t_sprite_info s_info;

	s_info.spritex = t_win.map_info.sprites[i].x - player.pos_x;
	s_info.spritey = t_win.map_info.sprites[i].y - player.pos_y;
	s_info.inv_d = 1.0 / (player.plane_x * player.dir_y -
						player.plane_y * player.dir_x);
	s_info.transf_x = s_info.inv_d * (player.dir_y * s_info.spritex -
						player.dir_x * s_info.spritey);
	s_info.transf_y = s_info.inv_d * (player.plane_x * s_info.spritey -
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

int				get_sprite_color(t_image t_img_s, t_sprite_info s_info,
				int j, int d)
{
	int	color;
	int tex_x;
	int tex_y;

	tex_y = ((d * t_img_s.y_i) / s_info.height) / 256;
	tex_x = (int)(256 * (j - s_info.draw_startx) *
			t_img_s.x_i / s_info.width) / 256;
	color = t_img_s.p_color[t_img_s.line_bytes * tex_y / 4 + tex_x];
	return (color);
}
