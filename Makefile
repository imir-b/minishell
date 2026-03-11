# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/11 23:05:00 by vlad              #+#    #+#              #
#    Updated: 2026/03/11 23:05:00 by vlad             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
.SILENT:
endif

SHELL			=	zsh

# ------------------------------------------------------------------------------
# exe
# ------------------------------------------------------------------------------

NAME			=	minishell

# ------------------------------------------------------------------------------
# dir
# ------------------------------------------------------------------------------

SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	inc

SUB_DIRS		=	parsing \
					utils \
					utils/string \
					utils/gnl

# ------------------------------------------------------------------------------
# files
# ------------------------------------------------------------------------------

SRC				=	$(filter-out $(SRC_DIR)/grammar.c, $(wildcard $(SRC_DIR)/*.c)) \
					$(foreach dir, $(SUB_DIRS), $(wildcard $(SRC_DIR)/$(dir)/*.c))

OBJ				=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# ------------------------------------------------------------------------------
# flags
# ------------------------------------------------------------------------------

MAKEFLAGS 		+=	--no-print-directory
MAKEFLAGS		+=	-j8

CFLAGS			=	-Wall -Wextra -Werror -g3

CPPFLAGS		=	-I $(INC_DIR)

INCLUDE_LIB		=

# ------------------------------------------------------------------------------
# colors
# ------------------------------------------------------------------------------

RED				=	\033[31;1m
BLU				=	\033[34;1m
CYAN			=	\033[36;1m
PUR				=	\033[35;1m
END				=	\033[0m

# ------------------------------------------------------------------------------
# rules
# ------------------------------------------------------------------------------

all:			$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(wildcard $(INC_DIR)/*.h)
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
	@echo -en "\xe2\x94\x8f\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -e "\xe2\x94\x81\xe2\x94\x93"
	@echo -en "\xe2\x94\x83$(CYAN)      compiling the sources �        $(END)\xe2\x94\x83\n"
	@echo -en "\xe2\x94\x97\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -e "\xe2\x94\x81\xe2\x94\x9b"
	@cc -g $(OBJ) $(INCLUDE_LIB) $(CFLAGS) $(CPPFLAGS) -o $(NAME)
	@echo -en "\xe2\x94\x8f\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -e "\xe2\x94\x81\xe2\x94\x93"
	@echo -en "\xe2\x94\x83$(CYAN)         everything ok, ready!        $(END)\xe2\x94\x83\n"
	@echo -en "\xe2\x94\x97\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -en "\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81\xe2\x94\x81"
	@echo -e "\xe2\x94\x81\xe2\x94\x9b"

clean:
	@rm -rf $(OBJ_DIR)
	@echo -en "$(CYAN)Cleaning objects...$(END)\n"

fclean: 		clean
	@rm -rf $(NAME)
	@echo -en "$(CYAN)Cleaning binary...$(END)\n"

re: 			fclean all

.PHONY:			all clean fclean re