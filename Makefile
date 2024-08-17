# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otodd <otodd@student.42london.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 13:06:47 by otodd             #+#    #+#              #
#    Updated: 2024/08/17 17:05:43 by otodd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= 	gcc
YELLOW		=	\033[1;33m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
BLUE		=	\033[1;34m
CYAN		=	\033[1;36m
NC			=	\033[0m


CFLAGS 		= 	-Wall -Wextra -Werror -std=c99 -g -fPIC -D_POSIX_C_SOURCE=200809L
NAME		= 	minishell

SRC_DIR 	= 	src
OBJ_DIR 	= 	obj
OBJ_DIRS	=	$(OBJ_DIR) \
				$(OBJ_DIR)/ft_builtins \
				$(OBJ_DIR)/ft_env \
				$(OBJ_DIR)/ft_executor \
				$(OBJ_DIR)/ft_expander \
				$(OBJ_DIR)/ft_gc \
				$(OBJ_DIR)/ft_parser \
				$(OBJ_DIR)/ft_tokeniser_helpers 

INC_DIR 	= 	include
LIBFT_DIR 	= 	libft

SRCS		=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/ft_utils.c \
				$(SRC_DIR)/ft_tests.c \
				$(SRC_DIR)/ft_signals.c \
				$(SRC_DIR)/ft_lexer.c \
				$(SRC_DIR)/ft_init.c \
				$(SRC_DIR)/ft_errs.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_utils.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_typers.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_reindex.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_pop.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_new.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_move_before.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_last.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_insert.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_finders.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_dup.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_delone.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_clear.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_token_add.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_quotes.c \
				$(SRC_DIR)/ft_tokeniser_helpers/ft_bool_checks.c \
				$(SRC_DIR)/ft_parser/ft_parser.c \
				$(SRC_DIR)/ft_parser/ft_parser_utils.c \
				$(SRC_DIR)/ft_parser/ft_parser_heredoc.c \
				$(SRC_DIR)/ft_gc/ft_tokeniser_gc.c \
				$(SRC_DIR)/ft_gc/ft_general_gc.c \
				$(SRC_DIR)/ft_gc/ft_executor_gc.c \
				$(SRC_DIR)/ft_expander/ft_expander.c \
				$(SRC_DIR)/ft_executor/ft_executor.c \
				$(SRC_DIR)/ft_executor/ft_executor_io.c \
				$(SRC_DIR)/ft_executor/ft_executor_io_ext.c \
				$(SRC_DIR)/ft_executor/ft_executor_utils.c \
				$(SRC_DIR)/ft_executor/ft_executor_redirs.c \
				$(SRC_DIR)/ft_executor/ft_executor_worker.c \
				$(SRC_DIR)/ft_executor/ft_executor_builtins.c \
				$(SRC_DIR)/ft_executor/ft_executor_worker_launcher.c \
				$(SRC_DIR)/ft_env/ft_env.c \
				$(SRC_DIR)/ft_env/ft_env_helpers.c \
				$(SRC_DIR)/ft_builtins/ft_unset.c \
				$(SRC_DIR)/ft_builtins/ft_pwd.c \
				$(SRC_DIR)/ft_builtins/ft_export.c \
				$(SRC_DIR)/ft_builtins/ft_exit.c \
				$(SRC_DIR)/ft_builtins/ft_env.c \
				$(SRC_DIR)/ft_builtins/ft_echo.c \
				$(SRC_DIR)/ft_builtins/ft_cd.c


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

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_parser/%.c $(INC_DIR)/minishell.h | dir
	@echo "[$(CYAN)MINISH$(NC)]    Compiling $< --> $@"
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/ft_expander/%.c $(INC_DIR)/minishell.h | dir
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
