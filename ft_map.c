#include "ft_cub3d.h"

/*

next steps :
	- amelioration du ray casting -> stockage des lignes verticales dans une image (ajout floor et ceiling)
	- lien entre map parsée et affichage d'une image
	- ajout de la mobilité
*/

/*

mlx_hook(mlx_win_list_t *win_ptr, int x_event, int x_mask, int (*funct_ptr)(), void *param)
funct_ptr --> ft_keys
param --> winndow ou player

mlx_hook(s.win.ptr, 2, 0, ft_key, &s);

int		ft_key(int key, void *arg) --> arg = param de mlx_hook ?


*/


void	print_map(t_window t_win, int **map)
{
	int	nb_lines;
	int	nb_columns;
	int	i;
	int	j;

	nb_lines = t_win.map_info.nb_lines;
	nb_columns = t_win.map_info.nb_columns;
	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (j < nb_columns)
		{
			if (map[i][j] == -1)
				printf(" ");
			else if (map[i][j] == 'N' - '0' || map[i][j] == 'S' - '0' ||
					map[i][j] == 'E' - '0' || map[i][j] == 'W' - '0')
				printf("%c", map[i][j] + '0');
			else
				printf("%d", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_map_info(t_map_info map_info)
{
	printf("resolution_x = %d\n", map_info.resolution_x);
	printf("resolution_y = %d\n", map_info.resolution_y);
	printf("path_img_N = %s\n", map_info.path_no);
	printf("path_img_S = %s\n", map_info.path_so);
	printf("path_img_E = %s\n", map_info.path_ea);
	printf("path_img_W = %s\n", map_info.path_we);
	printf("path_img_sprite = %s\n", map_info.path_sprite);
	printf("floor_colors = [%d, %d, %d]\n", map_info.f_colors[0], map_info.f_colors[1], map_info.f_colors[2]);
	printf("ceiling_colors = [%d, %d, %d]\n", map_info.c_colors[0], map_info.c_colors[1], map_info.c_colors[2]);
	printf("direction = %c\n", map_info.start.direction);
	printf("start_line = %d\n", map_info.start.line);
	printf("start_column = %d\n", map_info.start.column);
}





int main()
{
	char *map_file_path = "./map/map.cub";
	t_window	t_win;
	int		fd;
	int		nb_read;
	int		res_get_map;
	int		check_map;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		return (fd);
	nb_read = set_data_map_info(fd, &t_win.map_info);
	if (nb_read == -1)
		return (free_map_info_data(&t_win.map_info));
	res_get_map = parse_map(&t_win, map_file_path, fd, nb_read);

	check_map = check_map_with_propagation(t_win);

	printf("\ncheck_map = %d\n", check_map);
//	printf("nb_read = %d\n\n", nb_read);
//	print_map_info(t_win.map_info);
	printf("\n");
//	printf("get_map = %d\n", res_get_map);
//	printf("nb_lines = %d, nb_columns = %d\n", t_win.map_info.nb_lines, t_win.map_info.nb_columns);
	print_map(t_win, t_win.map);
	close(fd);
}