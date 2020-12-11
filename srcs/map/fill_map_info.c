/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:47:03 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/11 13:37:55 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_map_info(t_map_info *map_info)
{
	map_info->path_no = NULL;
	map_info->path_so = NULL;
	map_info->path_ea = NULL;
	map_info->path_we = NULL;
	map_info->path_sprite = NULL;
	map_info->start.line = -1;
	map_info->is_valid = 1;
	map_info->resolution_x = -1;
	map_info->f_colors[0] = -1;
	map_info->c_colors[0] = -1;
}

int		free_map_info_data(t_map_info *map_info)
{
	if (map_info->path_no)
		free(map_info->path_no);
	if (map_info->path_so)
		free(map_info->path_so);
	if (map_info->path_ea)
		free(map_info->path_ea);
	if (map_info->path_we)
		free(map_info->path_we);
	if (map_info->path_sprite)
		free(map_info->path_sprite);
	return (-1);
}

char	*trim_images_path(t_game *g, char *line)
{
	char *path;

//	path = ft_strtrim(line + 3, " ");
	path = malloc_trim_lst(g, line);
	return (path);
}

int	get_images_path(t_game *g, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (!(g->window.map_info.path_no = trim_images_path(g, line + 3))) // mallocs a gerer et proteger
			return (-1);
	}
	else if (!ft_strncmp(line, "SO ", 3))
	{
		if (!(g->window.map_info.path_so = trim_images_path(g, line + 3))) // mallocs a gerer et proteger
			return (-1);
	}
	else if (!ft_strncmp(line, "WE ", 3))
	{
		if (!(g->window.map_info.path_we = trim_images_path(g, line + 3))) // mallocs a gerer et proteger
			return (-1);
	}
	else if (!ft_strncmp(line, "EA ", 3))
	{
		if (!(g->window.map_info.path_ea = trim_images_path(g, line + 3))) // mallocs a gerer et proteger
			return (-1);
	}
	else if (!ft_strncmp(line, "S ", 2))
	{
		if (!(g->window.map_info.path_sprite = trim_images_path(g, line + 2))) // mallocs a gerer et proteger
			return (-1);
	}
	else
		return (0);
	return (1);
}

int	get_floor_ceiling_color(t_game *g, char *line)
{
	if (!ft_strncmp(line, "F ", 2))
		return (get_map_floor(&g->window.map_info, line + 2));
	else if (!ft_strncmp(line, "C ", 2))
		return (get_map_ceiling(&g->window.map_info, line + 2));
	else
		return (0);
}

int		fill_map_info(char *line, t_game *g)
{
	int	res;

	res = 0;
	if (!line[0])
		return (0);
	res += get_map_resolution(g, line); // OK
	res += get_images_path(g, line);
	res += get_floor_ceiling_color(g, line); // OK
	
	return (res);
}

int		set_data_map_info(int fd, t_game *g, int nb_read,
						int nb_param)
{
	int		size;
	char	*line;
	int		res;

	line = NULL;
	size = 1;
	init_map_info(&g->window.map_info);
	while (nb_param < 8 && ((size = get_next_line(fd, &line)) > 0))
	{
		nb_read++;
		res = fill_map_info(line, g);
		if (res == -1)
			return (free_error(line));
		nb_param += res;
		free_line(&line);
	}
	free_line(&line);
	g->window.map_info.nb_sprites = 0;
	if (nb_param != 8)
		nb_read = -1;
	return (nb_read);
}

int		**free_all_lines_and_map(int ***tab, int i_tab)
{
	int	i;

	i = 0;
	while (i < i_tab)
		free((*tab)[i++]);
	free(*tab);
	return (NULL);
}
