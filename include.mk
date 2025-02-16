LIBFT_DIR = ./libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include

SRCS = src/minishell.c src/lexer.c src/lexer_checking.c src/buildins.c src/env.c src/expander.c \
	src/parser.c src/redirections.c src/signals.c \
	utils/linked_list.c utils/free.c utils/utils1.c \


OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR)/include
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lhistory
CFLAGS += $(INCLUDES)
