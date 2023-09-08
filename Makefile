NAME = cub3d
#
PREF_SRC = src
PREF_OBJ = obj
#
HF_PATH = hf
HEADER = -I$(HF_PATH)
#
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
FSANITIZE = -fsanitize=address
#
SRC = $(addprefix $(PREF_SRC)/,|)
OBJ = $(patsubst $(PREF_SRC)/%.c, $(PREF_OBJ)/%.o, $(SRC))
#
all: $(NAME)
	@echo > /dev/null
#
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(SRC) -o $@
	@echo "Executable file $(NAME) created successfully"
#
$(PREF_OBJ)/%.o: $(PREF_SRC)/%.c Makefile
	@mkdir -p $(PREF_OBJ)
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@
#
clean:
	@rm -rf $(PREF_OBJ)
#
fclean: clean
	@rm -r $(NAME)
#
re: fclean all
#
.PHONY: all clean fclean re