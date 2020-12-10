#include "../../includes/cub3d.h"

int	save_image(char *path, char *buffer)
{
	int fd;
	int	len;
	
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd == -1)
		return (-1);
	len = ft_strlen(buffer);
	write(fd, buffer, len);
	return (1);
}
