NAME = cub3D

LIBFT = /Users/cvesta/Desktop/cub/libft

MLXLIB = /Users/cvesta/Desktop/cub/mlx

HEADER = cub3d.h

SRCS = adds.c adds2.c bmp.c check.c main.c map_set.c map_set2.c monitor_raycast.c monitor_sprites.c motion.c move.c parser.c parser2.c  parser3.c parser4.c parser5.c raycast.c setup.c setup2.c setup3.c setup4.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -I

MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit

CC = gcc

RM = rm -rf

.c.o:
	$(CC) $(FLAGS) $(HEADER) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(MLXLIB)
	cp $(MLXLIB)/libmlx.dylib ./
	$(CC) $(OBJS) $(MLX) $(LIBFT)/libft.a -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(MLXLIB)
	$(RM) ./libmlx.dylib
	$(RM) $(OBJS)

fclean:     clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFT)

re:     fclean all
	$(MAKE) re -C $(LIBFT)

.PHONY:     all clean fclean re