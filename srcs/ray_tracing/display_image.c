/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:21:16 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 14:08:54 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_image	get_correct_wall(t_session t_ses, t_ray ray)
{
	t_image	t_img;

	if (!ray.side)
	{
		if (ray.step.x > 0)
			t_img = t_ses.images.so;
		else
			t_img = t_ses.images.no;
	}
	else
	{
		if (ray.step.y > 0)
			t_img = t_ses.images.ea;
		else
			t_img = t_ses.images.we;
	}
	return (t_img);
}

void	vertical_line_to_image(t_game game, t_ray ray)
{
	t_image			t_img_src;
	t_pixel_info	pix;

//	pix.line_height = (int)(LINE_HEIGHT_STD / ray.dist_wall); // LINE_HEIGHT ou t_win.x_w ??
	pix.line_height = (int)((double)game.window.y_w * HEIGHT_FACTOR / ray.dist_wall); // LINE_HEIGHT ou t_win.x_w ??
	t_img_src = get_correct_wall(game.session, ray);
	pix.x_img = get_x_texture_coord(game.player, ray, t_img_src);
	pix.x_coord = ray.x;
	ft_put_ceiling_to_image(game.window, &pix, game.img);
	ft_put_line_to_image(game.window, t_img_src, &pix, game.img);
	ft_put_floor_to_image(game.window, &pix, game.img);
}

void	ft_put_line_to_image(t_window t_win, t_image t_img_src,
		t_pixel_info *pix, t_image t_img_new)
{
	int		y_off;
	double	y_step;
	int		i;
	int		color;

	pix->y_img = 0;
	y_step = (double)t_img_src.y_i / (double)pix->line_height;
	y_off = ft_max(y_step * (pix->line_height - t_win.y_w) / 2, 0);
	i = 0;
	while (i < pix->line_height && pix->y_coord < t_win.y_w)
	{
		pix->y_img = (int)(i * y_step + y_off);
		color = t_img_src.p_color[pix->x_img +
				t_img_src.line_bytes * pix->y_img / 4];
		 t_img_new.p_color[pix->x_coord +
		 	t_img_new.line_bytes * pix->y_coord / 4] = color;
		i++;
		pix->y_coord++;
	}
}

void	ft_put_ceiling_to_image(t_window t_win, t_pixel_info *pix,
								t_image t_img_new)
{
	int		y_limit;
	int		color;

	color = 16 * 16 * 16 * 16 * t_win.map_info.c_colors[0] +
			16 * 16 * t_win.map_info.c_colors[1] +
			t_win.map_info.c_colors[2];
	y_limit = ft_max((t_win.y_w - pix->line_height) / 2, 0);
	pix->y_coord = 0;
	while (pix->y_coord < y_limit)
	{
		t_img_new.p_color[pix->x_coord +
			t_img_new.line_bytes * pix->y_coord / 4] = color;
		pix->y_coord++;
	}
}

void	ft_put_floor_to_image(t_window t_win, t_pixel_info *pix,
							t_image t_img_new)
{
	int		y_limit;
	int		color;

	color = 16 * 16 * 16 * 16 * t_win.map_info.f_colors[0] +
			16 * 16 * t_win.map_info.f_colors[1] +
			t_win.map_info.f_colors[2];
	y_limit = t_win.y_w;
	while (pix->y_coord < y_limit)
	{
		t_img_new.p_color[pix->x_coord +
			t_img_new.line_bytes * pix->y_coord / 4] = color;
		pix->y_coord++;
	}
}
