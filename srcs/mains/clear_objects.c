/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 08:40:20 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/12 16:36:07 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*malloc_lst(t_game *game, int size)
{
	void	*ptr;
	t_list	*elem;

	if (!(ptr = malloc(size)))
		return (NULL);
	if (!(elem = ft_lstnew(ptr)))
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(&game->ptrs, elem);
	return (ptr);
}

int		malloc_trim_lst(t_game *game, char *s1, char c)
{
	char	*ptr;
	t_list	*elem;

	if ((c == 'N' && game->window.map_info.path_no) ||
		 (c == 'S' && game->window.map_info.path_so) ||
		 (c == 'E' && game->window.map_info.path_ea) ||
		 (c == 'W' && game->window.map_info.path_we) ||
		 (c == 's' && game->window.map_info.path_sprite))
		 return (-12);
	if (!(ptr = ft_strtrim(s1, " ")))
		return (-8);
	if (!(elem = ft_lstnew(ptr)))
		return (free_error_int(ptr, -8));
	ft_lstadd_back(&game->ptrs, elem);
	if (c == 'N')
		game->window.map_info.path_no = ptr;
	if (c == 'S')
		game->window.map_info.path_so = ptr;
	if (c == 'E')
		game->window.map_info.path_ea = ptr;
	if (c == 'W')
		game->window.map_info.path_we = ptr;
	if (c == 's')
		game->window.map_info.path_sprite = ptr;
	return (2);
}

int		free_all_ptr(t_game *game)
{
	ft_lstclear(&game->ptrs, free);
	clear_session_images(game);
	return (0);
}

int		free_line(char **line, int err)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (err);
}

void		clear_session_images(t_game *game)
{
	if (game->session.images.no.image)
		mlx_destroy_image (game->session.id, game->session.images.no.image);
	if (game->session.images.so.image)
		mlx_destroy_image (game->session.id, game->session.images.so.image);
	if (game->session.images.ea.image)
		mlx_destroy_image (game->session.id, game->session.images.ea.image);
	if (game->session.images.we.image)
		mlx_destroy_image (game->session.id, game->session.images.we.image);
	if (game->session.images.sprite.image)
		mlx_destroy_image (game->session.id, game->session.images.sprite.image);
}