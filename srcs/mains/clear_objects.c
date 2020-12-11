/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 08:40:20 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/11 09:37:49 by bjacob           ###   ########lyon.fr   */
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

int		free_all_ptr(t_game *game)
{
	ft_lstclear(&game->ptrs, free);
	return (0);
}

int		free_line(char **line)
{
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (-1);
}
