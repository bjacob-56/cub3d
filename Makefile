SRCS	=   srcs/events/event_handler.c srcs/events/move.c\
			srcs/mains/clear_objects.c srcs/mains/cub3d.c srcs/mains/errors.c srcs/mains/init.c\
			srcs/map/check_map.c srcs/map/fill_map_info.c srcs/map/get_map_info.c srcs/map/parse_map.c\
			srcs/maths/maths.c\
			srcs/ray_tracing/display_image.c srcs/ray_tracing/ray_projection.c srcs/ray_tracing/sprites_display.c srcs/ray_tracing/sprites_utils.c\
			srcs/save_image/save_image.c

OBJS = ${SRCS:.c=.o}

LIBFT = ./libft/libft.a
LIBMLX = libmlx.dylib

INC		= includes/cub3d.h
NAME	= cub3d
CC		= clang
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -I./includes -L. -lmlx -L./libft -lft

$(NAME) :	$(OBJS) $(INC) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS) :	$(INC)

.c.o:
	$(CC) -c $< -o $@

$(LIBFT) :
	@$(MAKE) all -C ./libft 

$(LIBMLX) : 
	@$(MAKE) all -C ./minilibx_mms_20200219
	mv ./minilibx_mms_20200219/libmlx.dylib .

all :		$(NAME)

clean :
	$(RM) $(OBJS)
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./minilibx_mms_20200219

fclean : 	clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(LIBMLX)

re :		fclean all

.PHONY :	all clean fclean re $(LIBFT) $(LIBMLX)
