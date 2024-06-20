# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/16 13:09:08 by ssottori          #+#    #+#              #
#    Updated: 2024/06/20 14:19:04 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -std=c99 -I/Library/Developer/CommandLineTools/SDKs/MacOSX14.4.sdk/usr/include
LDFLAGS = -L/opt/homebrew/Cellar/readline/8.2.10/lib
NAME = minishell
LIBFT_DIR = libft
SRCS = parser/main.c \
		parser/signals.c \
		parser/env.c \

OBJS = $(SRCS:.c=.o)
LIBS = -L/opt/homebrew/opt/readline/lib -lreadline -L$(LIBFT_DIR)/build -lft
LIBFT = $(LIBFT_DIR)/build/libft.a

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
	$(MAKE) -s -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all