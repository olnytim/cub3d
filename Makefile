NAME = cub3D
#
PREF_SRC = src
PREF_OBJ = obj
#
LIBFT_PATH = libft
LIBFTA = $(LIBFT_PATH)/libft.a
MINILIBX_PATH = minilibx-linux
MINILIBXA = $(MINILIBX_PATH)/libmlx.a
#
HF_PATH = hf
HEADER = -I$(HF_PATH)
MLX_HEADER = -I$(MINILIBX_PATH)
#
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
FSANITIZE = #-fsanitize=address
MINILIBX = -L./minilibx-linux -lmlx -lm -lXext -lX11
#
SRC = $(addprefix $(PREF_SRC)/, main.c check_utils.c check_map.c check_values.c check_colors.c check.c exit.c)
OBJ = $(patsubst $(PREF_SRC)/%.c, $(PREF_OBJ)/%.o, $(SRC))
#
# Mac implementation
#--------------------------------
all: add $(NAME)
	@echo > /dev/null
#
$(NAME): $(OBJ) $(LIBFTA)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(SRC) $(LIBFTA) -o $@
	@echo "Executable file $(NAME) created successfully!"
#
$(PREF_OBJ)/%.o: $(PREF_SRC)/%.c Makefile
	@mkdir -p $(PREF_OBJ)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(HEADER) -c $< -o $@
#---------------------------------
#
add:
	@make -C $(LIBFT_PATH)
#
clean:
	@rm -rf $(PREF_OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf *.dSYM
#
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFTA)
#
re: fclean all
#
.PHONY: all add clean fclean re
#
# Linux implementation
#-------------------------------
# all: add $(NAME)
# 	@echo > /dev/null
# #
# $(NAME): $(OBJ) $(LIBFTA)
# 	@$(CC) $(CFLAGS) $(SRC) $(LIBFTA) $(MINILIBXA) -o $@
# 	@echo "Executable file $(NAME) created successfully!"
# #
# $(PREF_OBJ)/%.o: $(PREF_SRC)/%.c Makefile
# 	@mkdir -p $(PREF_OBJ)
# 	@$(CC) $(CFLAGS) $(HEADER) $(MLX_HEADER) -c $< -o $@
# #
# add:
# 	@make -C $(LIBFT_PATH)
# 	@make -C $(MINILIBX_PATH)
# clean:
# 	@rm -rf $(PREF_OBJ)
# 	@$(MAKE) -C $(LIBFT_PATH) clean
# 	# @$(MAKE) -C $(MINILIBX_PATH) clean
# 	@rm -rf *.dSYM
# #
# fclean: clean
# 	@rm -f $(NAME)
# 	@rm -f $(LIBFTA)
# 	# @rm -f $(MINILIBXA)
# #
# re: fclean all
# #
# .PHONY: all add clean fclean re
#--------------------------------