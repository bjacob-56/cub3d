/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:22:15 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/08 15:28:59 by bjacob           ###   ########lyon.fr   */
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
//	mlx_destroy_window(game->session.id, game->window.window);
	ft_display_image(game->session, game->window, game->player);
	dprintf(1, "dirx = %f, diry = %f\n", game->player.dir_x, game->player.dir_y);
	return (0);
}

int		ft_key(int key, t_game *game)
{
	if (key == LEFT)
		turn_player(game, 1);
	if (key == RIGHT)
		turn_player(game, -1);
//	mlx_key_hook(game->window.window, &print_key, game);

	return (1);
}