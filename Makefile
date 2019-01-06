# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/30 12:55:46 by rschramm          #+#    #+#              #
#    Updated: 2017/11/14 14:27:22 by rschramm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ls

LIBFT = ./libft/libftprintf.a
LIBFTHEAD = -I ./libft/includes/

GCC = gcc
HEADERS = -I ./includes/
FLAGS += -fPIC
SRC = ./src/ls.c \
	  ./src/preprocessor.c \
	  ./src/vector.c \
	  ./src/get_data.c \
	  ./src/print.c \
	  ./src/processor.c \

COMPILE = $(GCC) $(FLAGS) $(SRC) $(HEADERS) $(LIBFTHEAD) $(LIBFT) -shared -o $(NAME) -g
TEST_MAIN = $(GCC) $(FLAGS) $(HEADERS) $(LINK) $(LIBFT) $(SRC) -o $(NAME) ./libft/*.o -g

OUTPUTBUILD = echo "\033[32mBuilding LS\033[0m"
OUTPUTCLEAN = echo "\033[31mRemoving Objects\033[0m"
OUTPUTFCLEAN = echo "\033[31mRemoving Executable\033[0m"
OUTPUTGO = echo "\033[92mSystem Ready :D\033[0m"
OUTPUTLIB = echo "\033[36;21mRebuilding Lib\033[0m"
OUTPUTRE = echo "\033[96;21mRebuilding LS\033[0m"

all: $(NAME)

$(NAME):
	@cd libft && make re
	@$(OUTPUTBUILD)
	@$(COMPILE)
	@$(TEST_MAIN)
	@$(OUTPUTGO)

clean:
	@$(OUTPUTCLEAN)
	@rm -f $(OBJ)

fclean: clean
	@$(OUTPUTFCLEAN)
	@rm -f $(NAME)
	@rm -f $(TESTNAME)

re:
	@$(OUTPUTRE)
	@make fclean
	@make

.PHONY: all clean fclean re
