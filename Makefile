NAME = so_long

CFLAG = -Wall -Wextra -Werror

SRC = test2.c \

SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRCS:.c=.o)

INCLUDE = -I ./include/

MLX_LIB = mlx/

MLX_FLAGS = -L./minilibx-linux -I minilibx-linux -lmlx -lX11 -Lmlx -lm -lz -lXext