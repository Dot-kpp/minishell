NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBFT = ./lib/libft/libft.a

SRCS = 	./src/main.c 

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
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o minishell
	@echo "Your shit is compiled"
	@echo ""


clean:
	@rm -rf $(NAME) *.out *.exe ./src/*.o ./minishell
	@echo "(๐ อกโฏอส อก)๐"

fclean: clean
	@rm -rf $(NAME) *.out *.exe ./src/*.o ./lib/libft/*.a ./lib/libft/src/*.o ./minishell
	@echo ""
	@echo "Your shit is clean af!"
	@echo ""
	@echo "(๐ อกโฏอส อก)๐"
	@echo ""

re:	fclean all