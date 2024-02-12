CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
ifdef DEBUG
CFLAGS	+= -fsanitize=adress -g3
endif
LIBFT	= Libft/
MLX		= minilibx-linux/
SRCS	= cub3d.c check_elems.c check_orientations.c check_colors.c
OBJS	= ${SRCS:.c=.o}
NAME	= cub3D

all		: ${NAME}

${NAME}	: ${OBJS}
		${MAKE} -C ${LIBFT}
		${CC} ${CFLAGS} -lXext -lX11 $^ ${LIBFT}libft.a -o $@

%.o		: %.c
		${CC} ${CFLAGS} -Imlx -c $< -o $@

clean	:
		rm -f ${OBJS} ${OBJSBONUS}
		${MAKE} clean -C ${LIBFT}
		${MAKE} clean -C ${MLX}

fclean	: clean
		rm -f ${NAME}
		${MAKE} fclean -C ${LIBFT}

debug	:
		${MAKE} DEBUG=1

re		: fclean all

bonus	: ${OBJSBONUS}
		${MAKE} -C ${LIBFT}
		${CC} ${CFLAGS} -Lmlx -lmlx -framework OpenGL -framework AppKit $^ ${LIBFT}libft.a -o ${NAME}

.PHONY	:	all clean fclean re