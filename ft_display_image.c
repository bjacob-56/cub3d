/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:21:16 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/06 12:29:34 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

t_image	get_correct_wall(t_session t_ses, t_ray ray)
{
	t_image	t_img;

	if (!ray.side)
	{
		if (ray.step.x > 0)
			t_img = t_ses.images.ea;
		else
			t_img = t_ses.images.we;
	}
	else
	{
		if (ray.step.y > 0)
			t_img = t_ses.images.no;
		else
			t_img = t_ses.images.so;
	}
	return (t_img);
}

int		get_x_texture_coord(t_player player, t_ray ray, t_image t_img)
{
	double	texture_x;
	int		texture_coord;

	if (!ray.side)
		texture_x = player.pos_y + ray.dist_wall * ray.dir.y;
	else
		texture_x = player.pos_x + ray.dist_wall * ray.dir.x;
	texture_x -= floor(texture_x);
	if ((!ray.side && ray.step.x > 0) || (ray.side && ray.step.y < 0)) // magie magie
		texture_x = 1 - texture_x;
	texture_coord = (int)(t_img.x_i * texture_x); 				// a voir s'il faut inverser si ray.step < 0
	return (texture_coord);
}

void	draw_wall_vertical_line(t_session t_ses, t_window t_win,
		t_player player, t_ray ray)
{
	t_image			t_img;
	int				x_texture_coord;
	t_pixel_info	pix;

// hauteur de la ligne a tracer
	pix.line_height = (int)(LINE_HEIGHT_STD / ray.dist_wall);

// dessin de la ligne verticale de la bonne texture
	t_img = get_correct_wall(t_ses, ray);

// calcul du x de la texture
	pix.x_img = get_x_texture_coord(player, ray, t_img);
	pix.x_coord = ray.x;

	ft_draw_line_image(t_ses.id, t_win, t_img, pix);
}

void	ft_draw_line_image(void *mlx_ptr, t_window t_win,
		t_image t_img, t_pixel_info pix)
{
	int		y_off;
	double	y_step;
	int		i;
	int		color;

//	pix.x_img = ft_min(pix.x_img, t_img.x_i - 1); // a voir si -1 ou non // vraiment nécessaire ?
	pix.y_img = 0;
	y_step = (double)t_img.y_i / (double)pix.line_height;
	pix.y_coord = ft_max((t_win.y_w - pix.line_height) / 2, 0);
	y_off = ft_max(y_step * (pix.line_height - t_win.y_w) / 2, 0);
	i = 0;
	while (i < pix.line_height && pix.y_coord < t_win.y_w) // a ajuster ?
	{
		pix.y_img = (int)(i * y_step + y_off);
		color = t_img.p_color[pix.x_img + t_img.line_bytes * pix.y_img / 4];
		mlx_pixel_put(mlx_ptr, t_win.window, pix.x_coord, pix.y_coord, color);
		i++;
		pix.y_coord++;
	}
}
