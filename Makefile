# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2022/10/31 00:04:10 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	./pipex

OBJ_DIR		:=	./OBJ
SRC_DIR		:=	./src
INC_DIR		:=	./include
LIB_DIR		:=	./lib

SRC			:=	pipex/pipex.c \
				pipex/pipex_error.c \
				pipex/pipex_check_input.c

OBJ			:=	$(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC))

#============== LIBRARIES ===============#

LIBFT		:=	libft
LIB_LIBFT	:=	$(LIB_DIR)/$(LIBFT)
LIB_LIB_ARC	:=	$(LIB_LIBFT)/$(LIBFT).a

LIB_LIST	:=	$(LIB_LIB_ARC)

#=============== COLOURS ================#

BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
CYAN	:= \033[36;1m
RESET	:= \033[0m

#============= COMPILATION ==============#

INCLUDE		:=	-I $(INC_DIR)\
				-I $(LIB_LIBFT)/include

LIB			:=

CC			:=	gcc
CFL			:=	-Wall -Werror -Wextra $(if DEBUG,-g)
COMPILE		:=	$(CC) $(CFL)

echo:
	@echo $(SRC)

#========================================#
#============== RECIPIES  ===============#
#========================================#

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): LIB $(OBJ) 
	@$(COMPILE) $(INCLUDE) $(OBJ) -o $(NAME) $(LIB_LIST)
	@echo "$(CYAN)$(BOLD)COMPILING COMPLETE$(RESET)"

$(OBJ_DIR)/%.o:$(SRC_DIR)/*/%.c | $(OBJ_DIR)
	@$(COMPILE) -o $@ -c $< $(INCLUDE)
	@echo "$(CYAN)COMPILING: $(notdir $<)$(RESET)"

debug: flclean
	@$(MAKE) DEBUG=1

flclean: lclean fclean

lclean:
	@make -C $(LIB_LIBFT) clean
	@$(RM) $(LIB_LIB_ARC)

clean:
	@mkdir -p $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(NAME)

re: fclean all

tclean: fclean
	rm -f $(EXE)

#========================================#
#============== LIBRARIES ===============#
#========================================#

LIB: $(LIB_LIST)

$(LIB_LIB_ARC):
	@make -C $(LIB_LIBFT)

#========================================#
#============ MISCELLANEOUS =============#
#========================================#

.PHONY: all clean fclean tclean re test

.DEFAULT_GOAL := all
