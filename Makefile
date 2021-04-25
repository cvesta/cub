NAME = cub3D

LIBFT = /Users/cvesta/Desktop/cub/libft

MLXLIB = /Users/cvesta/Desktop/cub/mlxlib

HEADER = cub3d.h

SRCS = adds.c adds2.c bmp.c check.c main.c map_set.c map_set2.c monitor_raycast.c monitor_sprites.c motion.c move.c parser.c parser2.c  parser3.c parser4.c parser5.c raycast.c setup.c setup2.c setup3.c setup4.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror -I

MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit

.c.o:
	@gcc $(FLAGS) $(HEADER) -c $< -o $(<:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(MLXLIB)
	@cp $(MLXLIB)/libmlx.dylib ./
	@gcc $(OBJS) $(MLX) $(LIBFT)/libft.a -o $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT)
	@$(MAKE) clean -C $(MLXLIB)
	@rm -rf ./libmlx.dylib
	@rm -rf $(OBJS)

fclean:     clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

re:     fclean all
	@$(MAKE) re -C $(LIBFT)

.PHONY:     all clean fclean re