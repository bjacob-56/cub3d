/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:48:26 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 15:49:28 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	close_window(t_game *game) // window a fermer   DestroyNotify
{
	mlx_destroy_window(game->session.id, game->window.window);
	return (0);
}

int	ft_key_press(int key, t_game *game)
{
	if (key == LEFT)
		game->player.move.turn_left = 1;
	else if (key == RIGHT)
		game->player.move.turn_right = 1;
	else if (key == W || key == UP)
		game->player.move.straight_pos = 1;
	else if (key == S || key == DOWN)
		game->player.move.straight_neg = 1;
	else if (key == A)
		game->player.move.side_left = 1;
	else if (key == D)
		game->player.move.side_right = 1;
	else if (key == ESC)
		close_window(game);
	return (0);
}

int		ft_key_release(int key, t_game *game)
{
	if (key == LEFT)
		game->player.move.turn_left = 0;
	else if (key == RIGHT)
		game->player.move.turn_right = 0;
	else if (key == W || key == UP)
		game->player.move.straight_pos = 0;
	else if (key == S || key == DOWN)
		game->player.move.straight_neg = 0;
	else if (key == A)
		game->player.move.side_left = 0;
	else if (key == D)
		game->player.move.side_right = 0;
	return (0);
}


int		ft_move_player(t_game *game)
{
	if (game->player.move.turn_left == 1)
		turn_player(game, 1);
	if (game->player.move.turn_right == 1)
		turn_player(game, -1);
	if (game->player.move.straight_pos == 1)
		move_player_straight(game, 1);
	if (game->player.move.straight_neg == 1)
		move_player_straight(game, -1);
	if (game->player.move.side_left == 1)
		move_player_side(game, -1);
	if (game->player.move.side_right == 1)
		move_player_side(game, 1);
	ft_display_image(*game, game->session, game->window, game->player);
	return (0);
}
