# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbin-nas <mbin-nas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 14:21:58 by smuhamma          #+#    #+#              #
#    Updated: 2023/08/10 19:08:24 by mbin-nas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS = utils.c sprite.c save.c read_map.c re_errors.c raycasting.c position.c path.c parse_map.c init.c header.c get_next_line.c get_data.c \
		free.c events.c display.c cub3d.c colour.c check_data.c add_sprite.c move.c map_check.c init2.c path2.c

OBJS	= ${SRCS:.c=.o}

LIBFT	= libft/libft.a

MINILIBX= minilibx_opengl/libmlx.a

CFLAGS	=	-Wall -Werror -Wextra 

%.o: %.c	gcc $(CFLAGS) -o $@ -c $<

$(NAME):	${OBJS}
			make -C minilibx_opengl
			make -C libft
			make bonus -C libft
			gcc -framework OpenGL -framework AppKit -g -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX)

all:		${NAME}

clean:
			rm -f ${OBJS}
			make clean -C libft

fclean:		clean
			rm -f ${NAME} cub.bmp
			make clean -C minilibx_opengl
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean
