/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 11:21:15 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/08 11:21:15 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_map_resolution(t_map_info *map_info, char *line_bis)
{
	while (*line_bis == ' ')
		line_bis++;
	map_info->resolution_x = 0;
	while (ft_isdigit(*line_bis))
		map_info->resolution_x = 10 * map_info->resolution_x
		+ (*(line_bis++) - '0');
	while (*line_bis == ' ')
		line_bis++;
	map_info->resolution_y = 0;
	while (ft_isdigit(*line_bis))
		map_info->resolution_y = 10 * map_info->resolution_y
		+ (*(line_bis++) - '0');
	while (*line_bis == ' ')
		line_bis++;
	if (*line_bis)
		return (-1);
	return (1);
}

int	get_map_floor(t_map_info *map_info, char *line_bis)
{
	int	i;

	i = 0;
	while (i < 3)
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
			return (-1);
		i++;
	}
	while (*line_bis == ' ')
		line_bis++;
	if (*line_bis)
		return (-1);
	return (1);
}

int	get_map_ceiling(t_map_info *map_info, char *line_bis)
{
	int i;

	i = 0;
	while (i < 3)
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
			return (-1);
		i++;
	}
	while (*line_bis == ' ')
		line_bis++;
	if (*line_bis)
		return (-1);
	return (1);
}
