# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 13:06:47 by otodd             #+#    #+#              #
#    Updated: 2024/06/12 12:29:51 by ssottori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

YELLOW		=	\033[1;33m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
NC			=	\033[0m

CC 			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror -g
NAME		= 	minishell

SRC_DIR 	= 	parser
OBJ_DIR 	= 	obj
INC_DIR 	= 	include
LIBFT_DIR 	= 	libft

SRCS		= 	$(SRC_DIR)/signals.c \
				$(SRC_DIR)/main.c \

OBJS 		= 	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT 		= 	$(LIBFT_DIR)/build/libft.a

HEADERS		= 	-I$(INC_DIR)

LIBS		=	-L$(LIBFT_DIR)/build -lft


all: $(LIBFT) $(NAME)

dir:
	@if [ ! -d "obj" ]; then \
		echo "[$(GREEN)MINISH$(NC)]    Creating obj directory..."; \
		mkdir -p obj; \
	fi

$(NAME): $(OBJS)
	@echo "[$(BLUE)MINISH$(NC)]    Building $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h | dir
	@echo "[$(CYAN)MINISH$(NC)]    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

clean:
	@echo "[$(YELLOW)MINISH$(NC)]    Cleaning object directory..."
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "[$(RED)MINISH$(NC)]    Cleaning executable directory..."
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
