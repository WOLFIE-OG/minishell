# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 13:06:47 by otodd             #+#    #+#              #
#    Updated: 2024/07/01 18:00:13 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= 	gcc

unamestr := $(shell uname)
ifeq ($(unamestr), Darwin)
	CC		=	/opt/homebrew/Cellar/gcc/14.1.0_1/bin/gcc-14
endif

YELLOW		=	\033[1;33m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
NC			=	\033[0m


CFLAGS 		= 	-Wall -Wextra -Werror -std=c99 -g
NAME		= 	minishell

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj
OBJ_DIRS	=	$(OBJ_DIR) \
				$(OBJ_DIR)/builtins

INC_DIR 	= 	include
LIBFT_DIR 	= 	libft

SRCS		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/signals.c \
				$(SRC_DIR)/env.c \
				$(SRC_DIR)/env_helpers.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/kill.c \
				$(SRC_DIR)/executor.c \
				$(SRC_DIR)/builtins/pwd.c \
				$(SRC_DIR)/builtins/cd.c \
				$(SRC_DIR)/builtins/export.c \
				$(SRC_DIR)/builtins/echo.c \
				$(SRC_DIR)/builtins/unset.c \
				$(SRC_DIR)/builtins/env.c \
				$(SRC_DIR)/builtins/exit.c \

OBJS 		= 	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT 		= 	$(LIBFT_DIR)/build/libft.a

HEADERS		= 	-I$(INC_DIR)

LIBS		=	-L$(LIBFT_DIR)/build -lft -lreadline


all: $(LIBFT) $(NAME)

dir:
	@for dir in $(OBJ_DIRS); do 									\
		if [ ! -d "$$dir" ]; then 												\
			echo "[$(GREEN)MINISH$(NC)]    Creating directory --> $$dir"; 		\
			mkdir -p $$dir; 													\
		fi; 																	\
	done

$(NAME): $(OBJS)
	@echo "[$(BLUE)MINISH$(NC)]    Building $@..."
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h | dir
	@echo "[$(CYAN)MINISH$(NC)]    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/builtins/%.c $(INC_DIR)/minishell.h | dir
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
