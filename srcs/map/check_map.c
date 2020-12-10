/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:45:56 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/10 14:45:58 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		**copy_map_to_map_bis(t_window t_win)
{
	int **map_bis;
	int	i;
	int	j;

	if (!(map_bis = ft_malloc_tab_2d(t_win)))
		return (0);
	i = 0;
	while (i < t_win.map_info.nb_lines)
	{
		j = -1;
		while (++j < t_win.map_info.nb_columns)
			map_bis[i][j] = t_win.map[i][j];
		i++;
	}
	return (map_bis);
}

void	check_next_point(t_window *t_win, int **map_bis, int i, int j)
{
	if (t_win->map_info.is_valid == -1)
		return ;
	if (map_bis[i][j] == -1 ||
		(i == 0 && map_bis[i][j] != 1) ||
		(j == 0 && map_bis[i][j] != 1) ||
		(i == t_win->map_info.nb_lines - 1 && map_bis[i][j] != 1) ||
		(j == t_win->map_info.nb_columns - 1 && map_bis[i][j] != 1))
	{
		t_win->map_info.is_valid = -1;
		return ;
	}
	else if (map_bis[i][j] == 1 ||
			map_bis[i][j] == 3)
		return ;
	else
	{
		map_bis[i][j] = 3;
		check_next_point(t_win, map_bis, i - 1, j);
		check_next_point(t_win, map_bis, i + 1, j);
		check_next_point(t_win, map_bis, i, j - 1);
		check_next_point(t_win, map_bis, i, j + 1);
	}
}

int		check_map_with_propagation(t_window *t_win)
{
	int	i_start;
	int	j_start;
	int **map_bis;

	if (!(map_bis = copy_map_to_map_bis(*t_win)))
		return (-1);
	i_start = t_win->map_info.start.column;
	j_start = t_win->map_info.start.line;
	if (t_win->map_info.is_valid == -1)
		return (-1);
	check_next_point(t_win, map_bis, i_start, j_start);
	free_all_lines_and_map(&map_bis, t_win->map_info.nb_lines);
	if (t_win->map_info.is_valid == 1)
		return (1);
	return (-1);
}
