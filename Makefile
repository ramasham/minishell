include include.mk
NAME = minishell
LIBFT_DIR = ./libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./include

OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR)/include
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lhistory
CFLAGS += $(INCLUDES)

all: libft $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft