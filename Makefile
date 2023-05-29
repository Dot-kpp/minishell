NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I./includes

LIBFT = ./lib/libft/libft.a
LIBRL = ./lib/readline/libreadline.a
LIBRLINE = readline-8.2

READLINE = -L./lib/ -lreadline

SRCS = 	./src/main.c \
		./src/init_data.c \
		./src/signals.c  \
		./src/errors.c \
		./src/pipes.c \
		./src/ft_append.c \
		./src/parsing.c \
		./src/parsing_utils.c \
		./src/free.c \
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

TEST_SRCS = ./unit_test/unit_tests.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

WHITE		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
CYAN 		:= \033[1;36m

.c.o:
	@ echo "$(YELLOW)Compiling: $(WHITE)$<"
	@ ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(LIBRL) $(LIBFT) $(NAME)

$(LIBRL) :
	@echo "$(YELLOW)Readline is compiling$(WHITE)"
	@echo "$(YELLOW)...$(WHITE)"
	@curl -O ftp://ftp.cwru.edu/pub/bash/$(LIBRLINE).tar.gz
	@tar -xf $(LIBRLINE).tar.gz
	@rm -rf $(LIBRLINE).tar.gz
	@cd $(LIBRLINE) && bash configure && make
	@mv ./$(LIBRLINE)/libreadline.a ./lib/readline
	@rm -rf $(LIBRLINE)
	@echo "$(GREEN)Readline is compiled$(WHITE)"
	@echo ""

$(LIBFT) :
	@echo "$(YELLOW)Your libft is compiling$(WHITE)"
	@echo "$(YELLOW)...$(WHITE)"
	@$(MAKE) -C lib/libft
	@echo "$(GREEN)libft is compiled$(WHITE)"
	@echo ""

$(NAME): COMPIL_MSG $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBRL) -lncurses -o $@
	@echo "$(GREEN)Your shit is compiled$(WHITE)"
	@echo ""

unit_test: $(TEST_OBJS) $(OBJ) $(LIBFT) $(LIBRL)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJ) $(LIBFT) $(LIBRL) -l$(LIBRLINE) -o test
	./test

COMPIL_MSG:
	@echo "$(YELLOW)Your shit is compiling$(WHITE)"
	@echo "$(YELLOW)...$(WHITE)"

clean:
	@rm -rf $(OBJ)
	@make clean -C lib/libft
	@echo "(👍 ͡ ͜ʖ ͡)👍"

fclean: clean
	@rm -rf $(NAME) $(LIBRL)
	@make fclean -C lib/libft
	@echo ""
	@echo "Your shit is clean af!"
	@echo ""
	@echo "(👍 ͡ ͜ʖ ͡)👍"
	@echo ""

re:	fclean all
