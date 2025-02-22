LIBFT_DIR = ./libft

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include

SRCS = src/minishell.c \
	src/lexer/lexer_checking_1.c  src/lexer/lexer_checking_2.c src/lexer/split_input.c src/lexer/split_operators.c src/lexer/lexer.c \
	src/expander/expander_utils.c src/expander/expander.c \
	src/parser/parser.c src/parser/redirections.c src/parser/handle_pipes.c \
	src/executor/buildins.c src/executor/executor.c \
	src/env.c src/signals.c \
	utils/free.c utils/linked_list.c utils/utils1.c \


OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(LIBFT_DIR)/include
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline -lhistory
CFLAGS += $(INCLUDES)
