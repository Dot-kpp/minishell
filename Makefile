NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I./includes -I ~/.brew/opt/readline/include

LIBFT = ./lib/libft/libft.a

READLINE = -L./lib/ -lreadline

SRCS = 	./src/main.c \
		./src/init_data.c \
		./src/signals.c  \
		./src/errors.c \
		./src/pipes.c \
		./src/builtins/ft_cd.c \
		./src/builtins/ft_echo.c \
		./src/builtins/ft_env.c \
		./src/builtins/ft_exit.c \
		./src/builtins/ft_export.c \
		./src/builtins/ft_pwd.c \
		./src/builtins/ft_unset.c \
		./src/builtins/call_builtin.c \
		./src/env/env_var.c

OBJ = $(SRCS:%.c=%.o)

.c.o:
	@ echo "$(YELLOW)Compiling: $(WHITE)$<"
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(LIBFT) $(NAME)

$(LIBFT) :
	@echo "Your libft is compiling"
	@echo "..."
	@$(MAKE) -C lib/libft
	@echo ""

$(NAME): $(OBJ)
	@echo "Your shit is compiling"
	@echo ""
	@echo ""
	@$(CC) -L ~/.brew/opt/readline/lib $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@
	@echo "Your shit is compiled"
	@echo ""


clean:
	@rm -rf $(OBJ)
	@make clean -C lib/libft
	@echo "(👍 ͡ ͜ʖ ͡)👍"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C lib/libft
	@echo ""
	@echo "Your shit is clean af!"
	@echo ""
	@echo "(👍 ͡ ͜ʖ ͡)👍"
	@echo ""

re:	fclean all
