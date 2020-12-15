/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:48:26 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/13 15:12:34 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_clean_prog(t_game *game)
{
	free_all_ptr(game);
	if (game->window.window)
		mlx_destroy_window(game->session.id, game->window.window);
	if (game->error == 1)
		write(1, "Cub3d over\n", 11);
	exit(0);
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
		ft_clean_prog(game);
	return (0);
}

int	ft_key_release(int key, t_game *game)
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

int	ft_move_player(t_game *game)
{
	int	change;

	change = 0;
	if (game->player.move.turn_left == 1)
		turn_player(game, 1, &change);
	if (game->player.move.turn_right == 1)
		turn_player(game, -1, &change);
	if (game->player.move.straight_pos == 1)
		move_player_straight(game, 1, &change);
	if (game->player.move.straight_neg == 1)
		move_player_straight(game, -1, &change);
	if (game->player.move.side_left == 1)
		move_player_side(game, -1, &change);
	if (game->player.move.side_right == 1)
		move_player_side(game, 1, &change);
	if (change && ft_display_image(game, game->window,
		game->player, 0) < 0)
		return (ft_error(-5, game));
	return (0);
}
