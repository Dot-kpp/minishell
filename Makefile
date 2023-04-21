NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I./includes

LIBFT = ./lib/libft/libft.a

READLINE = -L./lib/ -lreadline

SRCS = 	./src/main.c \
		./src/init_data.c \
		./src/signals.c  \
		./src/errors.c \
		./src/builtins/ft_cd.c \
		./src/builtins/ft_echo.c \
		./src/builtins/ft_env.c \
		./src/builtins/ft_exit.c \
		./src/builtins/ft_export.c \
		./src/builtins/ft_pwd.c \
		./src/builtins/ft_unset.c \
		./src/builtins/call_builtin.c \
		./src/env/env_var.c

OBJ = $(SRCS:%c=%o)

all: $(LIBFT) $(NAME)

$(LIBFT) :
	@echo "Your libft is compiling"
	@echo ""
	@$(MAKE) -C lib/libft
	@echo ""

$(NAME): $(OBJ)
	@echo "Your shit is compiling"
	@echo ""
	@echo ""
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -g -L./lib -lreadline -o minishell
	@echo "Your shit is compiled"
	@echo ""


clean:
	@rm -rf $(NAME) *.out *.exe ./src/*.o ./minishell
	@echo "(👍 ͡ ͜ʖ ͡)👍"

fclean: clean
	@rm -rf $(NAME) *.out *.exe ./src/*.o ./lib/libft/*.a ./lib/libft/src/*.o ./minishell
	@echo ""
	@echo "Your shit is clean af!"
	@echo ""
	@echo "(👍 ͡ ͜ʖ ͡)👍"
	@echo ""

re:	fclean all