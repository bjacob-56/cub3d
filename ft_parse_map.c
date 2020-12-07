#include "ft_cub3d.h"

int		**ft_malloc_tab_2d(t_window t_win)
{
	int	**map;
	int	i;

	if (!(map = malloc(sizeof(int*) * t_win.map_info.nb_lines)))
		return (NULL);
	i = 0;
	while (i < t_win.map_info.nb_lines)
	{
		if (!(map[i] = malloc(sizeof(int) * t_win.map_info.nb_columns))) // a voir si calloc adapté
			return (free_all_lines_and_map(&map, i));
		i++;
	}
	return (map);
}

int		check_cell_i_j(t_window *t_win, char *line, int i, int j)
{
	if (line[j] >= '0' && line[j] <= '2')
		t_win->map[i][j] = line[j] - '0';
	else if (line[j] == 'N' || line[j] == 'S' ||
		line[j] == 'E' || line[j] == 'W')
	{
		if (t_win->map_info.start.line != -1)
			return (-1);
		t_win->map_info.start.direction = line[j];
		t_win->map_info.start.line = i;
		t_win->map_info.start.column = j;
		t_win->map[i][j] = 0;
	}
	else if (line[j] == ' ')
		t_win->map[i][j] = -1;
	else
		return (-1);
	return (1);
	
}

int		fill_tab_map(t_window *t_win, int fd)
{
	int		i;
	int		j;
	int		len_line;
	int		size;
	char	*line;

	i = 0;
	size = get_next_line(fd, &line);
	while (size > 0 && i < t_win->map_info.nb_lines)
	{
		len_line = ft_strlen(line);
		j = -1;
		while (++j < len_line)
			if (check_cell_i_j(t_win, line, i, j) == -1)
				return (-1);
		while (j < t_win->map_info.nb_columns)
			t_win->map[i][j++] = -1;
		free(line);
		size = get_next_line(fd, &line);
		i++;
	}
	if (i != t_win->map_info.nb_lines)
		return (-1);
	return (1);
}

int		get_nb_lines_and_columns(t_window *t_win, int fd,
		int size, char **line)
{
	int	c_max;

	t_win->map_info.nb_columns = 0;
	t_win->map_info.nb_lines = 0;
	while (size > 0)
	{
		c_max = ft_max(t_win->map_info.nb_columns, ft_strlen(*line));
		t_win->map_info.nb_columns = c_max;
		t_win->map_info.nb_lines++;
		free(*line);
		size = get_next_line(fd, line);
	}
	if (size == -1)
		return (-1);
	free(*line);
	return (size);
}

int		parse_map(t_window *t_win, char *map_file_path, int fd, int nb_read)
{
	int		size;
	char	*line;

	size = get_next_line(fd, &line);
	while (size > 0 && !line[0])
	{
		free(line);
		size = get_next_line(fd, &line);
		nb_read++;
	}
	if (size <= 0)
		return (-1); // a gerer derriere
	if ((size = get_nb_lines_and_columns(t_win, fd, size, &line)) == -1 ||
		!(t_win->map = ft_malloc_tab_2d(*t_win)))
		return (-1);
	close(fd);
	fd = open(map_file_path, O_RDONLY); // autre maniere de revenir au debut du fichier ?
	while (nb_read-- > 0)
		get_next_line(fd, &line);
	if (fill_tab_map(t_win, fd) == -1)
	{
		free_all_lines_and_map(&t_win->map, t_win->map_info.nb_lines);
		return (-1);
	}
	return (1);
}
