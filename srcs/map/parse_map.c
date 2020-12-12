/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:29:50 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 16:09:00 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		**ft_malloc_tab_2d(t_game *game)
{
	int	**map;
	int	i;

	if (!(map = malloc_lst(game, sizeof(int*) *
				game->window.map_info.nb_lines)))
		return (NULL);
	i = 0;
	while (i < game->window.map_info.nb_lines)
	{
		if (!(map[i] = malloc_lst(game, sizeof(int) *
						game->window.map_info.nb_columns)))
			return (NULL); // gestion ici du free_all_lines_and_map ?
		i++;
	}
	return (map);
}

/*
** c = N/S/E/W --> 0
** c = 0 --> 0
** c = 1 --> 1
** c = 2 --> 2
** c = ' ' --> -1
*/

void	set_start_map(t_window *t_win, int i, int j, char *line)
{
	t_win->map_info.start.direction = line[j];
	t_win->map_info.start.line = j;
	t_win->map_info.start.column = i;
	t_win->map[i][j] = 0;
}

int		check_and_fill_cell_i_j(t_window *t_win, char *line, int i, int j)
{
	if (line[j] >= '0' && line[j] <= '2')
	{
		if (line[j] == '2')
		{
			t_win->map_info.sprites[t_win->map_info.nb_sprites].x = i + 0.5;
			t_win->map_info.sprites[t_win->map_info.nb_sprites++].y = j + 0.5;
		}
		t_win->map[i][j] = line[j] - '0';
	}
	else if (line[j] == 'N' || line[j] == 'S' ||
		line[j] == 'E' || line[j] == 'W')
	{
		if (t_win->map_info.start.line != -1)
		{
			t_win->map_info.is_valid = -1;
			return (-10);
		}
		set_start_map(t_win, i, j, line);
	}
	else if (line[j] == ' ')
		t_win->map[i][j] = -1;
	else
		return (-11);
	return (1);
}

int		fill_tab_map(t_game *g, int fd, int i, char **line)
{
	int		j;
	int		size;
	int		err;

	if (!(g->window.map_info.sprites =
		malloc_lst(g, sizeof(t_sprite) * g->window.map_info.nb_sprites)))
		return (-8);
	g->window.map_info.nb_sprites = 0;
	size = get_next_line(fd, line);
	while (size >= 0 && i < g->window.map_info.nb_lines)
	{
		j = -1;
		while (++j < ft_strlen(*line))
			if ((err = check_and_fill_cell_i_j(&g->window, *line, i, j)) < 0)
				return (err);
		while (j < g->window.map_info.nb_columns)
			g->window.map[i][j++] = -1;
		free_line(line, -1);
		size = get_next_line(fd, line);
		i++;
	}
	if (i != g->window.map_info.nb_lines)
		return (free_line(line, -6));
	close(fd);
	return (1);
}

int		parse_map(t_game *g, char *map_file_path, int fd, int nb_read)
{
	int		size;
	char	*line;
	int		err;

	line = NULL;
	size = get_next_line(fd, &line);
	while (size > 0 && !line[0]) // >0 || >= 0 ?
	{
		free_line(&line, -1);
		size = get_next_line(fd, &line);
		nb_read++;
	}
	if (size < 0 ||	(size = get_nb_lines_columns_sprites(&g->window, fd, size,
		&line))	== -1 || (fd = ft_reopen(fd, map_file_path)) == -1)
			return (free_line(&line, -6));
	if (!g->window.map_info.nb_lines)
		return (ft_close_file(fd, -1));
	if (!(g->window.map = ft_malloc_tab_2d(g)))
		return (-8);
	if (go_to_nb_read(fd, &line, nb_read) == -1)
		return (-6);
	if ((err = fill_tab_map(g, fd, 0, &line)) < 0)
		return (err);
	if (g->window.map_info.start.line == -1)
		return (-10);
	return (1);
}
