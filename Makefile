NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline
INCS = -I./src/libft -I./
LIBFT = -L./src/libft -lft
RM = rm -f

FILE = 	main \
		builtin/builtin \
		error/free_error \
		error/print_error \
		utils/list_utils \
		utils/str_utils \
		utils/split_utils \
		parsing/parsing_bundles \
		parsing/parsing_tokens \
		parsing/parsing_str \
		execute/execute_cmd \


SRCS = $(addprefix ./src/, $(addsuffix .c, $(FILE)))
OBJS = $(addprefix ./src/, $(addsuffix .o, $(FILE)))

%.o: %.c
	$(CC) $(INCS) -c $< -o $@

all : $(NAME)
$(NAME) : $(OBJS)
	make -C ./src/libft
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $@
	@echo "\033[31m⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣷⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "\033[33m⠀⠀⠀⠀⠀⠀⠀⣀⣶⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣦⣀⡀⠀⢀⣴⣇⠀⠀⠀⠀"
	@echo "\033[32m⠀⠀⠀⠀⠀⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "\033[34m⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀"
	@echo "\033[35m⠀⠀⠀⣴⣿⣿⣿⣿⠛⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀"
	@echo "\033[37m⠀⠀⣾⣿⣿⣿⣿⣿⣶⣿⣯⣭⣬⣉⣽⣿⣿⣄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀"
	@echo "\033[31m⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄"
	@echo "\033[33m⢸⣿⣿⣿⣿⠟⠋⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⣿⣿⣿⣿⡿⠛⠉⠉⠉⠉⠁"
	@echo "\033[32m⠘⠛⠛⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠃⠀⠀⠀⠀⠀"
# https://snskeyboard.com/dotart/

clean:
	make -C ./src/libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C ./src/libft fclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus