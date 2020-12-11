/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:21:50 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/11 19:05:41 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_int_to_buffer(char *buffer, int size, int *index)
{
	buffer[(*index)++] = size >> 0;
	buffer[(*index)++] = size >> 8;
	buffer[(*index)++] = size >> 16;
	buffer[(*index)++] = size >> 24;
}

void	fill_file_header(char *buffer, int *index, t_game game)
{
	int	file_size;

	file_size = game.img.line_bytes * game.window.y_w;
//	file_size = game.window.x_w * game.window.y_w * 4;
	buffer[(*index)++] = 'B';
	buffer[(*index)++] = 'M';
	put_int_to_buffer(buffer, file_size, index);
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 54;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 0;
}

void	fill_file_info(char *buffer, int *index, t_game game)
{
	int	img_width;
	int	img_height;
	int	i;	

	img_width = game.window.x_w;
	img_height = game.window.y_w;
	dprintf(1, "--> %d\n", img_height);
	buffer[(*index)++] = 40;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 0;
	put_int_to_buffer(buffer, img_width, index);
	put_int_to_buffer(buffer, img_height, index);
	buffer[(*index)++] = 1;
	buffer[(*index)++] = 0;
	buffer[(*index)++] = 24;
	buffer[(*index)++] = 0;
	i = -1;
	while (++i < 24)
		buffer[(*index)++] = 0;
/*
	40,0,0,0
	img w
	img y
	1,0
	24,0
	null (24o)
	*/
}

char *get_tab_colors(t_game game)
{
	char	*tab_bmp;
	int		p;
	int		e;
	int		l;

	tab_bmp = (char*)mlx_get_data_addr(game.img.image, &p, &l, &e);
	return (tab_bmp);
}

int	save_image(char *path, t_game game, int len)
{
	int fd;
	char	buffer[54 + len * 4];
//	char	buffer[54];
	int	index;
	int *tab_bmp;
	int x;
	int y;
	int j;
	
	index = 0;
	fill_file_header(buffer, &index, game);
	fill_file_info(buffer, &index, game);

	tab_bmp = game.img.p_color;
//	tab_bmp = get_tab_colors(game);
dprintf(1, "index avec boucle = %d\n", index);
//	y = game.window.y_w - 1;
//	while (y >= 0)
	y = 0;
	while (y < game.window.y_w)
	{
		x = 0;
		while (x < game.window.x_w)
		{
			buffer[index++] = tab_bmp[x + y * game.window.x_w] >> 0;
			buffer[index++] = tab_bmp[x + y * game.window.x_w] >> 8;
			buffer[index++] = tab_bmp[x + y * game.window.x_w] >> 16;
			x++;
		}
		j = 0;
		while (((x * 3 + j++) % 4 != 0))
			buffer[index++] = 0;
//		y--;
		y++;
	}

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd == -1)
		return (-1);
//	write(fd, buffer, 54);
//	write(fd, buffer, 54);
//	write(fd, tab_bmp, len );
dprintf(1, "index = %d\nlen = %d\n", index, len);
	write(fd, buffer, index);
	return (1);
}
