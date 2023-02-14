NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = 	./src/main.c 

OBJ = $(SRCS:%c=%o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Your shit is compiling"
	@echo ""
	@echo ""
	@$(CC) $(CFLAGS) $(OBJ) -o minishell
	@echo "Your shit is compiled"
	@echo ""


clean:
	@rm -rf $(NAME) *.out *.exe ./src/*.o ./minishell
	@echo "(👍 ͡ ͜ʖ ͡)👍"

fclean: clean
	@rm -rf $(NAME) *.out *.exe ./src/*.o ./minishell
	@echo ""
	@echo "Your shit is clean af!"
	@echo ""
	@echo "(👍 ͡ ͜ʖ ͡)👍"
	@echo ""

re:	fclean all