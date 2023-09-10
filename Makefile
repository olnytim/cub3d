NAME = cub3D
#
PREF_SRC = src
PREF_OBJ = obj
#
LIBFT_PATH = libft
LIBFTA = $(LIBFT_PATH)/libft.a
#
HF_PATH = hf
HEADER = -I$(HF_PATH)
#
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
FSANITIZE = -fsanitize=address
#
SRC = $(addprefix $(PREF_SRC)/, main.c check_args.c check.c exit.c)
OBJ = $(patsubst $(PREF_SRC)/%.c, $(PREF_OBJ)/%.o, $(SRC))
#
all: $(NAME)
	@echo > /dev/null
#
$(NAME): $(OBJ) $(LIBFTA)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFTA) -o $@
	@echo "Executable file $(NAME) created successfully"
#
$(PREF_OBJ)/%.o: $(PREF_SRC)/%.c Makefile
	@mkdir -p $(PREF_OBJ)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
#
$(LIBFTA):
	@make -C $(LIBFT_PATH)
#
clean:
	@rm -rf $(PREF_OBJ)
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -rf *.dSYM
#
fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)/libft.a
#
re: fclean all
#
.PHONY: all clean fclean re