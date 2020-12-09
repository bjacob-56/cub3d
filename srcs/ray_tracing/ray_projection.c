/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 12:13:25 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/09 11:51:38 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_ray_dir_and_delta(t_window t_win, t_player player, t_ray *ray)
{
	double	x;
	double	x_w;

	x = (double)(*ray).x;
	x_w = (double)t_win.x_w;
	(*ray).dir.x = player.dir_x + player.plane_x * (2 * (x / x_w) - 1);
	(*ray).dir.y = player.dir_y + player.plane_y * (2 * (x / x_w) - 1);
	if ((*ray).dir.y == 0)
		(*ray).delta.x = 0;
	else if ((*ray).dir.x == 0)
		(*ray).delta.x = 1;
	else
		(*ray).delta.x = fabs(1 / (*ray).dir.x);
	if ((*ray).dir.x == 0)
		(*ray).delta.y = 0;
	else if ((*ray).dir.y == 0)
		(*ray).delta.y = 1;
	else
		(*ray).delta.y = fabs(1 / (*ray).dir.y);
}

void	get_step_and_side_dist(t_player pl, t_ray *ray)
{
	if ((*ray).dir.x >= 0)
	{
		(*ray).step.x = 1;
		(*ray).side_dist.x = (1 - (pl.pos_x - pl.p_square_x)) * (*ray).delta.x;
	}
	else
	{
		(*ray).step.x = -1;
		(*ray).side_dist.x = (pl.pos_x - pl.p_square_x) * (*ray).delta.x;
	}
	if ((*ray).dir.y >= 0)
	{
		(*ray).step.y = 1;
		(*ray).side_dist.y = (1 - (pl.pos_y - pl.p_square_y)) * (*ray).delta.y;
	}
	else
	{
		(*ray).step.y = -1;
		(*ray).side_dist.y = (pl.pos_y - pl.p_square_y) * (*ray).delta.y;
	}
}

int		find_closest_wall(t_window t_win, t_player player,
		t_vector *p_square, t_ray *ray)
{
	int	hit;
	int	side;

	(*p_square).x = player.p_square_x;
	(*p_square).y = player.p_square_y;
	hit = 0;
	while (!hit) // comment checker le mur le plus proche ?
	{
		if ((*ray).side_dist.x <= (*ray).side_dist.y)
		{
			(*ray).side_dist.x += (*ray).delta.x;
			(*p_square).x += (*ray).step.x;
			side = 0;
		}
		else
		{
			(*ray).side_dist.y += (*ray).delta.y;
			(*p_square).y += (*ray).step.y;
			side = 1;
		}
		if (t_win.map[(int)(*p_square).x][(int)(*p_square).y] == 1) // attention a ne pas depasser la limite
			hit = 1;
	}
	return (side);
}

double	get_dist_wall(t_player player, t_ray ray, t_vector p_square)
{
	if (!ray.side)
		return (p_square.x - player.pos_x + (1 - ray.step.x) / 2) / ray.dir.x; // a voir si suffisant pour texture
	else
		return (p_square.y - player.pos_y + (1 - ray.step.y) / 2) / ray.dir.y;
}
