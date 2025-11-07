# Fractol - MVC implementation
NAME = fractol

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
INCLUDES = -I./includes -I./minilibx-linux
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

# Directories
SRC_DIR = src
MODEL_DIR = $(SRC_DIR)/model
VIEW_DIR = $(SRC_DIR)/view
CONTROLLER_DIR = $(SRC_DIR)/controller
OBJ_DIR = obj

# Source files
SRCS = $(SRC_DIR)/main.c \
       $(MODEL_DIR)/fractal_calc.c \
       $(VIEW_DIR)/render.c \
       $(CONTROLLER_DIR)/events.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# MLX library
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "$(GREEN)Downloading and building MiniLibX...$(RESET)"
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@make -C $(MLX_DIR) > /dev/null 2>&1 || echo "$(RED)MLX build warning (may be OK)$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiled: $<$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(RESET)"

mlx_clean:
	@if [ -d "$(MLX_DIR)" ]; then \
		make -C $(MLX_DIR) clean > /dev/null 2>&1; \
	fi
	@echo "$(RED)MLX cleaned$(RESET)"

mlx_fclean:
	@rm -rf $(MLX_DIR)
	@echo "$(RED)MLX removed$(RESET)"

re: fclean all

.PHONY: all clean fclean mlx_clean mlx_fclean re
