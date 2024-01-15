NAME	:= cub3d
CC		:= gcc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
DEBUG	:= -g
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/Libft
HEADERS	:= -I ./include -I $(LIBMLX)/include -I ./$(LIBFT)/src
LIB	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm

SRC	:= 	src/main.c \
		src/parsing_arguments.c \
		src/init/initialize_data.c \
		src/init/initialize_mlx.c \
		src/init/initialize_textures.c \
		src/init/init_utils.c \
		src/init/init_load.c \
		src/init/init_map.c \
		src/utils/draw_utils.c \
		src/utils/utils.c \
		src/render/render_main.c \
		src/render/render_dda.c \
		src/render/render_raycasting.c \
		src/render/render_textures.c \
		lib/get_next_line/get_next_line_utils.c \
		lib/get_next_line/get_next_line.c

OBJ	:= $(patsubst %.c,obj/%.o,$(SRC))

GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m

all: libmlx libft $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(YELLOW)Cloning MLX42$(RESET)"; \
		git clone https://github.com/codam-coding-college/MLX42 $(LIBMLX); \
	fi
		cmake $(LIBMLX) -DDEBUG=1 -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4;

libft:
	@if [ ! -d "$(LIBFT)" ]; then \
		echo "$(YELLOW)Cloning Libft$(RESET)"; \
		git clone https://github.com/Ling-Lang/Libft $(LIBFT); \
	fi
		@cd $(LIBFT) && make;

obj/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(DEBUG) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling $@$(RESET)"
	@$(CC) $(OBJ) $(LIB) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Finished compiling: $@$(RESET)"

clean:
	@echo "$(YELLOW)Cleaning object files$(RESET)"
	@rm -rf obj

fclean: clean
	@echo "$(YELLOW)Cleaning executable $(NAME)$(RESET)"
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx