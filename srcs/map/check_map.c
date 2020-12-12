/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:45:56 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 15:08:11 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		**copy_map_to_map_bis(t_game *game, t_window t_win)
{
	int **map_bis;
	int	i;
	int	j;

	if (!(map_bis = ft_malloc_tab_2d(game)))
		return (NULL);
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
		if (map_bis[i][j] == -1)
			t_win->map_info.is_valid = -11;
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

int		check_map_with_propagation(t_game *game, t_window *t_win)
{
	int	i_start;
	int	j_start;
	int **map_bis;

	if (!(map_bis = copy_map_to_map_bis(game, *t_win)))
		return (-8);
	i_start = t_win->map_info.start.column;
	j_start = t_win->map_info.start.line;
	if (t_win->map_info.is_valid < 0)
		return (t_win->map_info.is_valid);
	check_next_point(t_win, map_bis, i_start, j_start);
	if (t_win->map_info.is_valid == 1)
		return (1);
	return (t_win->map_info.is_valid);
}

int		go_to_nb_read(int fd, char **line, int nb_read)
{
	free_line(line, -1);
	while (nb_read-- > 0)
	{
		if (get_next_line(fd, line) == -1)
			return (free_line(line, -1));
	}
	return (1);
}

int		check_map_extension(char *map_path)
{
	int i;

	i = ft_strlen(map_path);
	if (i < 5 ||
		map_path[i - 4] != '.' ||
		map_path[i - 3] != 'c' ||
		map_path[i - 2] != 'u' ||
		map_path[i - 1] != 'b'
		)
		return (-1);
	return (1);
}