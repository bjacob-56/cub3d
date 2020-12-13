/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:22:15 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/13 10:28:57 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	move_player_straight(t_game *game, int signe, int *change)
{
	double	pos_x;
	double	pos_y;
	double	p_square_x;
	double	p_square_y;

	*change = 1;
	pos_x = game->player.pos_x;
	pos_y = game->player.pos_y;
	pos_x += signe * ONE_STEP * game->player.dir_x;
	pos_y += signe * ONE_STEP * game->player.dir_y;
	p_square_x = floor(pos_x);
	p_square_y = floor(pos_y);
	if (game->window.map[(int)p_square_x][(int)p_square_y] == 0 ||
		game->window.map[(int)p_square_x][(int)p_square_y] == 2)
	{
		game->player.pos_x = pos_x;
		game->player.pos_y = pos_y;
		game->player.p_square_x = p_square_x;
		game->player.p_square_y = p_square_y;
	}
	return (0);
}

int	move_player_side(t_game *game, int signe, int *change)
{
	double	pos_x;
	double	pos_y;
	double	p_square_x;
	double	p_square_y;

	*change = 1;
	pos_x = game->player.pos_x;
	pos_y = game->player.pos_y;
	pos_x += signe * ONE_STEP * game->player.dir_y;
	pos_y += (-1) * signe * ONE_STEP * game->player.dir_x;
	p_square_x = floor(pos_x);
	p_square_y = floor(pos_y);
	if (game->window.map[(int)p_square_x][(int)p_square_y] == 0 ||
		game->window.map[(int)p_square_x][(int)p_square_y] == 2)
	{
		game->player.pos_x = pos_x;
		game->player.pos_y = pos_y;
		game->player.p_square_x = p_square_x;
		game->player.p_square_y = p_square_y;
	}
	return (0);
}

int	turn_player(t_game *game, int signe, int *change)
{
	double	dir_x;
	double	dir_y;

	*change = 1;
	dir_x = game->player.dir_x;
	dir_y = game->player.dir_y;
	game->player.dir_x = dir_x * cos(signe * THETA) -
						dir_y * sin(signe * THETA);
	game->player.dir_y = dir_x * sin(signe * THETA) +
						dir_y * cos(signe * THETA);
	game->player.plane_x = game->player.dir_y;
	game->player.plane_y = -1 * game->player.dir_x;
	return (0);
}
