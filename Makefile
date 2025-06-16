NAME = so_long

SRCS = \
	src/main.c src/animate.c src/free_images.c src/free_images2.c \
	src/move_player_enemy.c src/read_map.c src/render_textures.c \
	src/render_textures2.c src/set_textures.c src/set_textures2.c \
	src/utils.c src/validate.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
LIBFT_DIR = libft
MLX_DIR = mlx_linux

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -Lminilibx-linux -lmlx_Linux -lX11 -lXext $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
