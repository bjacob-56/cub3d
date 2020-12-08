/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 11:21:18 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/08 11:21:18 by bjacob           ###   ########lyon.fr   */
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

int		fill_map_info(char *line, t_map_info *map_info)
{
	int	res;

	res = 1;
	if (!line[0])
		return (0);
	if (!ft_strncmp(line, "R ", 2))
		res = get_map_resolution(map_info, line + 2);
	else if (!ft_strncmp(line, "NO ", 3))
		map_info->path_no = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "SO ", 3))
		map_info->path_so = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "WE ", 3))
		map_info->path_we = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "EA ", 3))
		map_info->path_ea = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "S ", 2))
		map_info->path_sprite = ft_strtrim(line + 2, " ");
	else if (!ft_strncmp(line, "F ", 2))
		res = get_map_floor(map_info, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		res = get_map_ceiling(map_info, line + 2);
	else
		return (-1);
	return (res);
}

int		set_data_map_info(int fd, t_map_info *map_info)
{
	int		size;
	char	*line;
	int		res;
	int		nb_param;
	int		nb_read;

	nb_read = 0;
	nb_param = 0;
	size = 1;
	init_map_info(map_info);
	while (nb_param < 8 && ((size = get_next_line(fd, &line)) > 0))
	{
		nb_read++;
		res = fill_map_info(line, map_info);
		if (res == -1)
			return (free_error(line));
		nb_param += res;
		free(line);
	}
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
