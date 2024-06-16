# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/16 13:09:08 by ssottori          #+#    #+#              #
#    Updated: 2024/06/16 13:42:49 by ssottori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -std=c99 -I/Library/Developer/CommandLineTools/SDKs/MacOSX14.4.sdk/usr/include
LDFLAGS = -L/opt/homebrew/Cellar/readline/8.2.10/lib
NAME = minishell
SRCS = parser/main.c \
		parser/signals.c \

OBJS = $(SRCS:.c=.o)
LIBS = -L/opt/homebrew/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all