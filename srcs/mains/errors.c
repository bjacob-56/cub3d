/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 12:12:24 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/13 15:11:38 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*get_error_message(int err)
{
	if (err == -1)
		return ("The map is invalid\n");
	if (err == -2)
		return ("New image couldn't be created\n");
	if (err == -3)
		return ("Image start_image.bmp couldn't be created\n");
	if (err == -4)
		return ("New window couldn't be created\n");
	if (err == -5)
		return ("New image couldn't be created while moving the player\n");
	if (err == -6)
		return ("The map file couldn't be opened or read properly\n");
	if (err == -7)
		return ("The map file format is invalid\n");
	if (err == -8)
		return ("A malloc failed\n");
	if (err == -9)
		return ("The parsing of the map couldn't be done properly\n");
	if (err == -10)
		return ("Wrong number of start points defined in the map\n");
	if (err == -11)
		return ("A forbidden character was found in the map\n");
	if (err == -12)
		return ("The map parameters are incorrect\n");
	return ("");
}

int			ft_error(int err, t_game *game)
{
	char	*message;

	message = get_error_message(err);
	write(1, "Error\n", 6);
	write(1, message, ft_strlen(message));
	game->error = -1;
	ft_clean_prog(game);
	return (-1);
}

int			ft_main_error(void)
{
	write(1, "Error\n", 6);
	write(1, "Wrong inputs\n", 13);
	return (-1);
}

int			free_error_int(char *ptr, int err)
{
	free_error(ptr);
	return (err);
}

int			ft_close_file(int fd, int err)
{
	close(fd);
	return (err);
}
