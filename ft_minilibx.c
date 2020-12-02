#include  "mlx.h"

void	ft_open_minilibx(void)
{
	void	*init;
	void	*window;
	int		size_x;
	int		size_y;
	char	*window_title = "Fenetre_1";

	init = mlx_init();
	size_x = 852;
	size_y = 480;
	window = mlx_new_window(init, size_x, size_y, window_title);


//	mlx_clear_window(init, window);
}

int main()
{
	ft_open_minilibx();

}