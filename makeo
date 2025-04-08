include include.mk

NAME = minishell
LIBFT_DIR = ./libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./include

OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR)/include
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lhistory
CFLAGS += $(INCLUDES)

# ANSI color codes
YELLOW = \033[33m
RESET  = \033[0m

MAKEFLAGS += --silent

all: libft $(NAME)
	@echo "$(YELLOW)Make done$(RESET)"

libft:
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@echo "$(YELLOW)Clean done$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null
	@rm -f $(NAME)
	@echo "$(YELLOW)Fclean done$(RESET)"

re: fclean all
	@echo "$(YELLOW)Rebuild done$(RESET)"

.PHONY: all clean fclean re libft
