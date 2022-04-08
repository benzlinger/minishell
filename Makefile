# EXECUTABLE
NAME = ./minishell

# FLAGS
CC = gcc
CFLAGS = -lreadline -Wall -Wextra #-Werror #-g 

# COLORS
Y = "\033[33m"
P = "\033[93m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

# PATHS
SRC_PATH = ./src/
OBJ_PATH = ./obj/
UTILS_PATH = ./src/

# SOURCES
SRC =	$(SRC_PATH)main.c		$(SRC_PATH)lexer.c\
	$(SRC_PATH)utils_error.c	$(SRC_PATH)utils_lexer.c\
	$(SRC_PATH)debug.c
# OBJECTS
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

# RULES
all: $(NAME)
	@echo $(P)"           _       _     _          _ _ "$(X)
	@echo $(P)" _ __ ___ (_)_ __ (_)___| |__   ___| | |"$(X)
	@echo $(P)"| '_ ' _ \| | '_ \| / __| '_ \ / _ \ | |"$(X)
	@echo $(P)"| | | | | | | | | | \__ \ | | |  __/ | |"$(X)
	@echo $(P)"|_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|"$(X)
	@printf "\n\n"

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@sleep 0.2
	@printf $(UP)$(CUT)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo $(G)Finished [$@]$(X)
	@sleep 0.2
	@printf $(UP)$(CUT)

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) libft/libft.a
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@if [ -d "$(OBJ_PATH)" ]; then \
			rm -f -r $(OBJ_PATH); \
			echo $(R)Cleaning" "[$(OBJ) $(OBJ_PATH)]$(X); else \
			echo "No objects to remove."; \
	fi;
	@make -C libft clean

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			rm -f $(NAME); \
			echo $(R)Cleaning" "[$(NAME)]$(X);else \
			echo "No executable to remove."; \
	fi;
	@make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re
