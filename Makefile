# EXECUTABLE
NAME = ./minishell

# READLINE
LFR = -L$$HOME/.brew/opt/readline/lib -lreadline
LFRC = -I$$HOME/.brew/opt/readline/include

# FLAGS
CC = gcc
CFLAGS = -Wall -Wextra -g #-Werror

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
SRC =	$(SRC_PATH)main.c					$(SRC_PATH)lexer.c\
		$(SRC_PATH)utils_error.c			$(SRC_PATH)utils_lexer.c\
		$(SRC_PATH)signals.c				$(SRC_PATH)utils_free.c\
		$(SRC_PATH)utils_lexer2.c			$(SRC_PATH)parser.c\
		$(SRC_PATH)utils_parser.c			$(SRC_PATH)executer.c\
		$(SRC_PATH)builtins.c				$(SRC_PATH)utils_parser_types.c\
		$(SRC_PATH)utils_parser_dquote.c	$(SRC_PATH)export.c\
		$(SRC_PATH)utils_parser_command.c	$(SRC_PATH)utils_export.c\
		$(SRC_PATH)unset.c					$(SRC_PATH)utils_general.c\
		$(SRC_PATH)utils_parser_dquote2.c	$(SRC_PATH)utils_parser_heredoc.c\
		$(SRC_PATH)utils_parser_redirec.c	$(SRC_PATH)pipes.c\
		$(SRC_PATH)utils_executer_redirec.c $(SRC_PATH)utils_executer_redirec2.c\
		$(SRC_PATH)compatibility.c			$(SRC_PATH)utils_executer.c\
    	$(SRC_PATH)utils_parser_exitstatus.c	$(SRC_PATH)debug.c\

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
	@$(CC) $(CFLAGS) $(LFRC) -c -o $@ $< 
	@echo $(G)Finished [$@]$(X)
	@sleep 0.2
	@printf $(UP)$(CUT)

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) $(LFR) $(OBJ) -o $(NAME) libft/libft.a
	@echo $(G)Finished [$(NAME)]$(X)

clean:
	@if [ -d "$(OBJ_PATH)" ]; then \
			rm -f -r $(OBJ_PATH); \
			echo $(R)Cleaning" "[$(OBJ) $(OBJ_PATH)]$(X); else \
			echo "No objects to remove."; \
	fi;
	@$(MAKE) -C libft clean
	@rm -f .tmp.txt

fclean: clean
	@if [ -f "$(NAME)" ]; then \
			rm -f $(NAME); \
			echo $(R)Cleaning" "[$(NAME)]$(X);else \
			echo "No executable to remove."; \
	fi;
	@$(MAKE) -C libft fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all, clean, fclean, re
