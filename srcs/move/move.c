/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:22:15 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/09 11:53:25 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*

mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*funct_ptr)(), void *param)
funct_ptr --> ft_keys
param --> window ou player

mlx_hook(s.win.ptr, 2, 0, ft_key, &s);

int		ft_key(int key, void *arg) --> arg = param de mlx_hook ?


*/

int		print_key(int key, t_game *game)
{
	dprintf(1, "key = %d\n", key);
	return (1);
}

int		move_player_straight(t_game *game, int key)
{
	double	pos_x;
	double	pos_y;
	double	p_square_x;
	double	p_square_y;
	int		signe;

	signe = 1;
	if (key == S || key == DOWN)
		signe = -1;
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
	ft_display_image(game->session, game->window, game->player);
	return (0);
}

int		move_player_side(t_game *game, int key) // A CORRIGER
{
	double	pos_x;
	double	pos_y;
	double	p_square_x;
	double	p_square_y;
	int		signe;

	signe = 1;
	if (key == D)
		signe = -1;
	pos_x = game->player.pos_x;
	pos_y = game->player.pos_y;
	pos_x += signe * ONE_STEP * game->player.dir_y; // pas bon
	pos_y += signe * ONE_STEP * game->player.dir_x; // pas bon
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
	ft_display_image(game->session, game->window, game->player);
	return (0);
}

int		turn_player(t_game *game, int signe)
{
	double	dir_x;
	double	dir_y;

	dir_x = game->player.dir_x;
	dir_y = game->player.dir_y;
	game->player.dir_x = dir_x * cos(signe * THETA) -
						dir_y * sin(signe * THETA);
	game->player.dir_y = dir_x * sin(signe * THETA) +
						dir_y * cos(signe * THETA);
	game->player.plane_x = game->player.dir_y;
	game->player.plane_y = -1 * game->player.dir_x;
	ft_display_image(game->session, game->window, game->player);
	return (0);
}

int		close_window(t_game *game) // window a fermer
{
	mlx_destroy_window(game->session.id, game->window.window);
	return (0);
}

int		ft_key(int key, t_game *game)
{
	if (key == LEFT)
		turn_player(game, 1);
	if (key == RIGHT)
		turn_player(game, -1);
	if (key == W || key == S || key == UP || key == DOWN)
		move_player_straight(game, key);
	if (key == A || key == D)
		move_player_side(game, key);
	if (key == ESC)
		close_window(game);
	return (0);
}