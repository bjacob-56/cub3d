/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:17:21 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 14:17:35 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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