/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:47:03 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/13 16:17:53 by bjacob           ###   ########lyon.fr   */
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

int		get_images_path(t_game *g, char *line)
{
	int res;

	res = 0;
	if (!ft_strncmp(line, "NO ", 3))
		res = malloc_trim_lst(g, line + 3, 'N');
	else if (!ft_strncmp(line, "SO ", 3))
		res = malloc_trim_lst(g, line + 3, 'S');
	else if (!ft_strncmp(line, "EA ", 3))
		res = malloc_trim_lst(g, line + 3, 'E');
	else if (!ft_strncmp(line, "WE ", 3))
		res = malloc_trim_lst(g, line + 3, 'W');
	else if (!ft_strncmp(line, "S ", 2))
		res = malloc_trim_lst(g, line + 2, 's');
	return (res);
}

int		get_floor_ceiling_color(t_game *g, char *line)
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

	res = -1;
	if (!line[0])
		return (0);
	if (!ft_strncmp(line, "R ", 2))
		res += get_map_resolution(g, line);
	res += get_images_path(g, line);
	res += get_floor_ceiling_color(g, line);
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
		if (res < 0)
			return (free_line(&line, -12));
		nb_param += res;
		free_line(&line, -1);
	}
	free_line(&line, -1);
	g->window.map_info.nb_sprites = 0;
	if (nb_param != 8)
		nb_read = -12;
	return (nb_read);
}
