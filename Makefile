# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sblauens <sblauens@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 16:59:41 by sblauens          #+#    #+#              #
#    Updated: 2018/11/27 11:10:36 by sblauens         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src

OBJ_DIR = obj

INC_DIR = include

LIB_DIR = .

SRC_FILES = minishell.c env.c setenv.c builtins.c builtins_setenv.c

LIB_NAMES = libft

CC = clang

CFLAGS = -Wall -Wextra -Werror

GFLAGS = -g

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIB = $(addprefix $(LIB_DIR)/, $(LIB_NAMES))

CPPFLAGS = -I $(INC_DIR) $(addprefix -I , $(LIB))

LDFLAGS = $(addprefix -L , $(LIB))

LDLIBS = $(addprefix -, $(patsubst lib%, l%, $(LIB_NAMES)))

all: $(NAME)

dbg: CFLAGS = $(GFLAGS)

dbg: $(NAME)
	@echo "__debug__"

$(NAME): $(OBJ)
	@$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@
	@echo "minishell: linking"
	@echo "minishell: ready to fork !"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(LIB_NAMES) $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "minishell: compiling $@"

$(OBJ_DIR):
	@mkdir $@

$(LIB_NAMES):
	@make -C $(addprefix $(LIB_DIR)/, $@)

clean: clean_lib clean_minishell

clean_minishell:
	@rm -rf $(OBJ)
	@rmdir $(OBJ_DIR) 2> /dev/null || true
	@echo "minishell: objects removed."

clean_lib:
	@make clean -C $(LIB_NAMES)

fclean: fclean_lib fclean_minishell

fclean_minishell: clean_minishell
	@rm -rf $(NAME)
	@echo "minishell: exec removed."

fclean_lib:
	@make fclean -C $(LIB_NAMES)

re: fclean all

.PHONY: all clean fclean re $(LIB_NAMES)
