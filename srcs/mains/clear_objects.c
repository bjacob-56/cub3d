/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 08:40:20 by bjacob            #+#    #+#             */
/*   Updated: 2020/12/11 13:35:05 by bjacob           ###   ########lyon.fr   */
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

char		*malloc_trim_lst(t_game *game, char *s1)
{
	int		s_len;
	int		i;
	int		j;
	char	*res;
	t_list	*elem;

	if (!s1)
		return (NULL);
	s_len = ft_strlen(s1);
	i = 0;
	while (s1[i] && s1[i] == ' ')
		i++;
	s_len = s_len - 1;
	while (s_len > i && s1[s_len] == ' ')
		s_len--;
	if (!(res = malloc(sizeof(char) * (s_len - i + 2))))
		return (NULL);
	j = 0;
	while (i <= s_len)
		res[j++] = s1[i++];
	res[j] = '\0';
	if (!(elem = ft_lstnew(res)))
	{
		free(res);
		return (NULL);
	}
	ft_lstadd_back(&game->ptrs, elem);
	return (res);
}
