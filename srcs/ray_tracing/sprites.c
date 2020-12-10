/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 12:47:33 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 11:02:14 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	switch_dist(double *tab, int i, int j)
{
	int	temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

static void	switch_sprites(t_sprite *tab, int i, int j)
{
	t_sprite	temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

void	sort_sprites(t_sprite *tab, int nb_sprites, t_player p)
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