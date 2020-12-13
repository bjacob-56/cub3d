/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:21:50 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/13 12:43:57 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	write_int(int fd, int i, int size)
{
	write(fd, &i, size);
}

static void	fill_file_header(int fd, t_game game)
{
	int	file_size;

	file_size = game.window.x_w * game.window.y_w * 4 + 54;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write_int(fd, 0, 4);
	write_int(fd, 54, 4);
}

static void	fill_file_info(int fd, t_game game)
{
	int	img_width;
	int	img_height;
	int	bpp;

	img_width = game.window.x_w;
	img_height = game.window.y_w;
	bpp = game.img.bpp;
	write_int(fd, 40, 4);
	write(fd, &img_width, 4);
	write(fd, &img_height, 4);
	write_int(fd, 1, 2);
	write(fd, &bpp, 2);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
	write_int(fd, 0, 4);
}

static void	fill_file_body(int fd, t_game game)
{
	int	x;
	int	y;
	int color;

	y = game.window.y_w - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < game.window.x_w)
		{
			color = game.img.p_color[x + y * game.img.line_bytes / 4];
			write(fd, &color, 4);
			x++;
		}
		y--;
	}
}

int			save_image(char *name, t_game game)
{
	int		fd;
	char	*path;
	int		len;

	len = game.window.x_w * game.window.y_w;
	if (!(path = ft_strjoin("./saved_image/", name)))
		return (ft_error(-3, &game));
	if (ft_display_image(&game, game.window, game.player, 1) < 0)
		return (ft_error(-3, &game));
	fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		return (ft_error(-3, &game));
	fill_file_header(fd, game);
	fill_file_info(fd, game);
	fill_file_body(fd, game);
	free(path);
	free_all_ptr(&game);
	return (1);
}
