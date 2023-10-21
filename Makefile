NAME = cub3D

SYSTEM = $(shell uname -s)
#
PREF_SRC = src
PREF_OBJ = obj
#
LIBFT_PATH = libft
LIBFTA = $(LIBFT_PATH)/libft.a
#
HF_PATH = include
HEADER = -I$(HF_PATH)
#
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
FSANITIZE = -fsanitize=address
#
SRC = $(addprefix $(PREF_SRC)/, raycasting.c raycasting2.c \
	main.c check_utils.c check_map.c check_values.c check_colors.c \
	hooks.c check.c exit.c)
OBJ = $(patsubst $(PREF_SRC)/%.c, $(PREF_OBJ)/%.o, $(SRC))
#
ifeq ($(SYSTEM), Darwin)
	MINILIBX_PATH = minilibx-mac
	MLX_HEADER = -I$(MINILIBX_PATH)
	MINILIBXA = $(MINILIBX_PATH)/libmlx.a
	MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
	TMP =
else
	MINILIBX_PATH = minilibx-linux
	MLX_HEADER = -I$(MINILIBX_PATH)
	MINILIBXA = $(MINILIBX_PATH)/libmlx.a
	MLX_FLAGS = -L./$(MINILIBX_PATH) -lmlx -lm -lXext -lX11
	TMP = -I$(MINILIBX_PATH)
endif
#
all: add $(NAME)
	@echo > /dev/null
#
$(NAME): $(OBJ) $(LIBFTA)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(SRC) $(HEADER) $(LIBFTA) $(MINILIBXA) $(MLX_FLAGS) -o $@
	@echo "\033[36mExecutable file $(NAME) was created successfully!"
#
$(PREF_OBJ)/%.o: $(PREF_SRC)/%.c Makefile $(HF_PATH)/cub3D.h
	@mkdir -p $(PREF_OBJ)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(MLX_HEADER) $(HEADER) $(TMP) -c $< -o $@
#
add:
	@if [[ (! -e $(MINILIBXA)) || (! -e $(LIBFTA)) ]]; then \
		make -C $(LIBFT_PATH) ; \
		make -C $(MINILIBX_PATH) ; \
		echo "\033[32mLibrary libmlx.a was created successfully!" ; \
	fi
#
bonus: all
	@echo "\033[35mBonus file was compiled in the same file \033[36m'$(NAME)' \033[35msuccessfully!"
#
clean:
	@rm -rf $(PREF_OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MINILIBX_PATH) clean
	@rm -rf *.dSYM
#
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFTA)
	@rm -f $(MINILIBXA)
#
re: fclean all
#
.PHONY: all add clean fclean re
#