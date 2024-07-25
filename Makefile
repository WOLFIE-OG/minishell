# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssottori <ssottori@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 13:06:47 by otodd             #+#    #+#              #
#    Updated: 2024/07/25 20:12:54 by ssottori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= 	gcc
YELLOW		=	\033[1;33m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
NC			=	\033[0m


CFLAGS 		= 	-Wall -Wextra -Werror -std=c99 -g -fPIC
NAME		= 	minishell

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj
OBJ_DIRS	=	$(OBJ_DIR) \
				$(OBJ_DIR)/ft_builtins \
				$(OBJ_DIR)/ft_tokeniser_helpers \
				$(OBJ_DIR)/ft_env \
				$(OBJ_DIR)/ft_executor \
				$(OBJ_DIR)/ft_gc

INC_DIR 	= 	include
LIBFT_DIR 	= 	libft

SRCS		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/ft_signals.c \
				$(SRC_DIR)/ft_env/ft_env.c \
				$(SRC_DIR)/ft_env/ft_env_helpers.c \
				$(SRC_DIR)/ft_utils.c \
				$(SRC_DIR)/ft_init.c \
				$(SRC_DIR)/ft_tests.c \
				$(SRC_DIR)/ft_errs.c \
				$(SRC_DIR)/ft_executor/ft_executor.c \
				$(SRC_DIR)/ft_executor/ft_executor_helpers.c \
				$(SRC_DIR)/ft_gc/ft_executor_gc.c \
				$(SRC_DIR)/ft_gc/ft_general_gc.c \
				$(SRC_DIR)/ft_gc/ft_tokeniser_gc.c \
				$(SRC_DIR)/ft_builtins/ft_pwd.c \
				$(SRC_DIR)/ft_builtins/ft_cd.c \
				$(SRC_DIR)/ft_builtins/ft_export.c \
				$(SRC_DIR)/ft_builtins/ft_echo.c \
				$(SRC_DIR)/ft_builtins/ft_unset.c \
				$(SRC_DIR)/ft_builtins/ft_env.c \
				$(SRC_DIR)/ft_builtins/ft_exit.c \
				$(SRC_DIR)/ft_lexer.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_add.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_clear.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_delone.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_last.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_new.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_pop.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_size.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_utils.c
				

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_builtins/%.c $(INC_DIR)/minishell.h | dir
	@echo "[$(CYAN)MINISH$(NC)]    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_tokeniser_helpers/%.c $(INC_DIR)/minishell.h | dir
	@echo "[$(CYAN)MINISH$(NC)]    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_executor/%.c $(INC_DIR)/minishell.h | dir
	@echo "[$(CYAN)MINISH$(NC)]    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_gc/%.c $(INC_DIR)/minishell.h | dir
	@echo "[$(CYAN)MINISH$(NC)]    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_env/%.c $(INC_DIR)/minishell.h | dir
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
