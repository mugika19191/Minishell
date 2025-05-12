CC=cc 
FLAGS= -Wextra -Werror -Wall 
LIBFT_DIR = lib/ft_libft
LIBFT_A = $(LIBFT_DIR)/libft.a
SRC_DIR= src/
INCLUDE_FLAG = -Iinclude
SRC = $(SRC_DIR)actions.c $(SRC_DIR)built_in.c $(SRC_DIR)built_in_2.c $(SRC_DIR)exec_built_in.c\
 $(SRC_DIR)built_in_utils.c $(SRC_DIR)clean_quotes.c $(SRC_DIR)executor_2.c $(SRC_DIR)executor.c $(SRC_DIR)init.c $(SRC_DIR)main.c\
 $(SRC_DIR)quotes.c $(SRC_DIR)redir.c $(SRC_DIR)shell_split.c $(SRC_DIR)tokenizer_2.c\
$(SRC_DIR)tokenizer.c $(SRC_DIR)utils.c $(SRC_DIR)readline.c $(SRC_DIR)heredoc.c

OBJ = $(SRC:.c=.o)
NAME = minishell

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(FLAGS)  -g  $(OBJ) -o $(NAME) $(LIBFT_A) $(INCLUDE_FLAG) -lreadline

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

all: $(LIBFT_A) $(NAME)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all