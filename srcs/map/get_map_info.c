/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:47:58 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 17:39:09 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_map_resolution(t_game *g, char *line_bis)
{
	if (g->window.map_info.resolution_x != -1)
		return (-12);
	line_bis = line_bis + 2;
	while (*line_bis == ' ')
		line_bis++;
	g->window.map_info.resolution_x = 0;
	while (ft_isdigit(*line_bis) && g->window.map_info.resolution_x <= X_RES)
		g->window.map_info.resolution_x = 10 * g->window.map_info.resolution_x
		+ (*(line_bis++) - '0');
	while (ft_isdigit(*line_bis))
		line_bis++;
	while (*line_bis == ' ')
		line_bis++;
	g->window.map_info.resolution_y = 0;
	while (ft_isdigit(*line_bis) && g->window.map_info.resolution_y <= Y_RES)
		g->window.map_info.resolution_y = 10 * g->window.map_info.resolution_y
		+ (*(line_bis++) - '0');
	while (ft_isdigit(*line_bis))
		line_bis++;
	while (*line_bis == ' ')
		line_bis++;
	if (*line_bis)
		return (-12);
	return (2);
}

int	get_map_floor(t_map_info *map_info, char *line_bis)
{
	int	i;

	i = -1;
	if (map_info->f_colors[0] != -1)
		return (-12);
	while (++i < 3)
	{
		while (*line_bis == ' ')
			line_bis++;
		if (i > 0 && *line_bis == ',')
			line_bis++;
		while (*line_bis == ' ')
			line_bis++;
		map_info->f_colors[i] = 0;
		while (ft_isdigit(*line_bis) && map_info->f_colors[i] <= 255)
			map_info->f_colors[i] = 10 * map_info->f_colors[i]
			+ (*(line_bis++) - '0');
		if (map_info->f_colors[i] > 255)
			return (-12);
	}
	while (*line_bis == ' ')
		line_bis++;
	if (*line_bis)
		return (-12);
	return (2);
}

int	get_map_ceiling(t_map_info *map_info, char *line_bis)
{
	int i;

	i = -1;
	if (map_info->c_colors[0] != -1)
		return (-12);
	while (++i < 3)
	{
		while (*line_bis == ' ')
			line_bis++;
		if (i > 0 && *line_bis == ',')
			line_bis++;
		while (*line_bis == ' ')
			line_bis++;
		map_info->c_colors[i] = 0;
		while (ft_isdigit(*line_bis) && map_info->c_colors[i] <= 255)
			map_info->c_colors[i] = 10 * map_info->c_colors[i]
			+ (*(line_bis++) - '0');
		if (map_info->c_colors[i] > 255)
			return (-12);
	}
	while (*line_bis == ' ')
		line_bis++;
	if (*line_bis)
		return (-12);
	return (2);
}

int	get_nb_lines_columns_sprites(t_window *t_win, int fd,
		int size, char **line)
{
	int	c_max;
	int j;

	free_line(line, -1);
	t_win->map_info.nb_sprites = 0;
	t_win->map_info.nb_columns = 0;
	t_win->map_info.nb_lines = 0;
	while (size >= 0)
	{
		c_max = ft_max(t_win->map_info.nb_columns, ft_strlen(*line));
		j = 0;
		while (j < ft_strlen(*line))
			if ((*line)[j++] == '2')
				t_win->map_info.nb_sprites++;
		t_win->map_info.nb_columns = c_max;
		if (t_win->map_info.nb_lines > 0 || ft_strlen(*line) > 0)
			t_win->map_info.nb_lines++;
		if (!size)
			break ;
		free_line(line, -1);
		size = get_next_line(fd, line);
	}
	free_line(line, -1);
	return (size);
}

int	ft_reopen(int fd, char *map_file_path)
{
	close(fd);
	fd = open(map_file_path, O_RDONLY);
	return (fd);
}
