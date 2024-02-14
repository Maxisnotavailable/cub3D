# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molla <molla@student.42nice.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 08:46:35 by molla             #+#    #+#              #
#    Updated: 2024/02/14 10:59:39 by molla            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
ifdef DEBUG
CFLAGS	+= -fsanitize=address -g3
endif
LIBFT	= Libft/
MLX		= minilibx-linux/
SRCS	= cub3d.c ./Parsing/parsing.c ./Parsing/check_elems.c\
		./Parsing/check_orientations.c ./Parsing/check_colors.c\
		./Parsing/check_map_utils.c ./Parsing/check_map.c
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