/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:21:16 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/09 16:25:18 by bjacob           ###   ########lyon.fr   */
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
			t_img = t_ses.images.we;
		else
			t_img = t_ses.images.ea;
	}
	return (t_img);
}

/*
t_image	get_correct_wall(t_session t_ses, t_ray ray)
{
	t_image	t_img;

	if (!ray.side)
	{
		if (ray.step.x > 0)
			t_img = t_ses.images.we;
		else
			t_img = t_ses.images.ea;
	}
	else
	{
		if (ray.step.y > 0)
			t_img = t_ses.images.so;
		else
			t_img = t_ses.images.no;
	}
	return (t_img);
}
*/

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

////////////////////////////////////////

void	vertical_line_to_image(t_session t_ses, t_window t_win, t_image t_img_new,
		t_player player, t_ray ray)
{
	t_image			t_img_src;
	int				x_texture_coord;
	t_pixel_info	pix;

// hauteur de la ligne a tracer
	pix.line_height = (int)(LINE_HEIGHT_STD / ray.dist_wall);

// dessin de la ligne verticale de la bonne texture
	t_img_src = get_correct_wall(t_ses, ray);

// calcul du x de la texture
	pix.x_img = get_x_texture_coord(player, ray, t_img_src);
	pix.x_coord = ray.x;

	ft_put_ceiling_to_image(t_win, t_img_src, &pix, t_img_new);
	ft_put_line_to_image(t_win, t_img_src, &pix, t_img_new);
	ft_put_floor_to_image(t_win, t_img_src, &pix, t_img_new);
}

void	ft_put_line_to_image(t_window t_win,
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

void	ft_put_ceiling_to_image(t_window t_win,
		t_image t_img_src, t_pixel_info *pix, t_image t_img_new)
{
	int		y_limit;
	int		color;

	color = 16 * 16 * 16 * 16 * t_win.map_info.c_colors[0] +
			16 * 16 * t_win.map_info.c_colors[1] +
			t_win.map_info.c_colors[2];
	y_limit = ft_max((t_win.y_w - pix->line_height) / 2, 0);

	pix->y_coord = 0;
	while (pix->y_coord < y_limit) // a ajuster ?
	{
		t_img_new.p_color[pix->x_coord + t_win.x_w * pix->y_coord] = color; // pas sur
		pix->y_coord++;
	}
}


void	ft_put_floor_to_image(t_window t_win,
		t_image t_img_src, t_pixel_info *pix, t_image t_img_new)
{
	int		y_limit;
	int		color;

	color = 16 * 16 * 16 * 16 * t_win.map_info.f_colors[0] +
			16 * 16 * t_win.map_info.f_colors[1] +
			t_win.map_info.f_colors[2];
	y_limit = t_win.y_w;

	while (pix->y_coord < y_limit) // a ajuster ?
	{
		t_img_new.p_color[pix->x_coord + t_win.x_w * pix->y_coord] = color; // pas sur
		pix->y_coord++;
	}
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
	pix->y_coord = ft_max((t_win.y_w - pix->line_height) / 2, 0);
	y_off = ft_max(y_step * (pix->line_height - t_win.y_w) / 2, 0);
	i = 0;
	while (i < pix->line_height && pix->y_coord < t_win.y_w) // a ajuster ?
	{
		pix->y_img = (int)(i * y_step + y_off);
		color = t_img_src.p_color[pix->x_img + t_img_src.line_bytes * pix->y_img / 4];
		if (color)
			t_img_new.p_color[pix->x_coord + t_win.x_w * pix->y_coord] = color; // pas sur
//		mlx_pixel_put(mlx_ptr, t_win.window, pix->x_coord, pix->y_coord, color);
		i++;
		pix->y_coord++;
	}
}


t_image	vertical_sprite_line_to_image(t_session t_ses, t_window t_win, t_image t_img_new,
		t_player player, t_ray ray)
{
	t_image			t_img_src;
	int				x_texture_coord;
	t_pixel_info	pix;

// hauteur de la ligne a tracer
	pix.line_height = abs((int)(LINE_HEIGHT_STD / ray.dist_wall));

// dessin de la ligne verticale de la bonne texture
	t_img_src = t_ses.images.sprite;

// calcul du x de la texture
	pix.x_img = get_x_texture_coord(player, ray, t_img_src);

//	int	sprite_screenX = (int)((t_win.x_w / 2) * (1 + ray.side_dist.x / ray.side_dist.y));
//	pix.x_img = (int)((int)((256 * (ray.x - (sprite_screenX - t_img_src.x_i / 2)) *
//				t_img_src.x_i / pix.line_height)) / 256);

	pix.x_coord = ray.x;

//	ft_put_ceiling_to_image(t_win, t_img_src, &pix, t_img_new);
//	pix.y_coord = ft_max((t_win.y_w - pix.line_height) / 2, 0);
	ft_put_stripe_line_to_image(t_win, t_img_src, &pix, t_img_new);
//	ft_put_floor_to_image(t_win, t_img_src, &pix, t_img_new);
	return (t_img_new);
}