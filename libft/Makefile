# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rschramm <rschramm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/30 12:55:46 by rschramm          #+#    #+#              #
#    Updated: 2017/11/06 09:02:08 by rschramm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT = libft/ft_bzero.c \
	   libft/ft_bzerotype.c \
	   libft/ft_atoi.c \
	   libft/ft_itoa.c \
	   libft/ft_isalpha.c \
	   libft/ft_isdigit.c \
	   libft/ft_isalnum.c \
	   libft/ft_isascii.c \
	   libft/ft_isprint.c \
	   libft/ft_toupper.c \
	   libft/ft_tolower.c \
	   libft/ft_memset.c \
	   libft/ft_memcpy.c \
	   libft/ft_memccpy.c \
	   libft/ft_memmove.c \
	   libft/ft_memchr.c \
	   libft/ft_memcmp.c \
	   libft/ft_memalloc.c \
	   libft/ft_memdel.c \
	   libft/ft_heap_singleton.c \
	   libft/ft_vheap_singleton.c \
	   libft/ft_vheap_clear.c \
	   libft/ft_hmalloc.c \
	   libft/ft_hmemalloc.c \
	   libft/ft_hstrdup.c \
	   libft/ft_hstrndup.c \
	   libft/ft_hstrjoin.c \
	   libft/ft_vhstrjoin.c \
	   libft/ft_hfree.c \
	   libft/ft_heap_clear.c \
	   libft/ft_putchar.c \
	   libft/ft_putstr.c \
	   libft/ft_fputstr.c \
	   libft/ft_fputstr_fd.c \
	   libft/ft_fputstrn_fd.c \
	   libft/ft_putendl.c \
	   libft/ft_putnbr.c \
	   libft/ft_putchar_fd.c \
	   libft/ft_putstr_fd.c \
	   libft/ft_putendl_fd.c \
	   libft/ft_putnbr_fd.c \
	   libft/ft_strlen.c \
	   libft/ft_strdup.c \
	   libft/ft_strcpy.c \
	   libft/ft_strncpy.c \
	   libft/ft_strcat.c \
	   libft/ft_strncat.c \
	   libft/ft_strlcat.c \
	   libft/ft_strchr.c \
	   libft/ft_strchrrev.c \
	   libft/ft_strrchr.c \
	   libft/ft_strstr.c \
	   libft/ft_strnstr.c \
	   libft/ft_strcmp.c \
	   libft/ft_strncmp.c \
	   libft/ft_strnew.c \
	   libft/ft_strdel.c \
	   libft/ft_strclr.c \
	   libft/ft_striter.c \
	   libft/ft_striteri.c \
	   libft/ft_strmap.c \
	   libft/ft_strmapi.c \
	   libft/ft_strequ.c \
	   libft/ft_strnequ.c \
	   libft/ft_strsub.c \
	   libft/ft_strjoin.c \
	   libft/ft_strxjoin.c \
	   libft/ft_strtrim.c \
	   libft/ft_strsplit.c \
	   libft/ft_lstnew.c \
	   libft/ft_lstdelone.c \
	   libft/ft_lstdel.c \
	   libft/ft_lstadd.c \
	   libft/ft_lstiter.c \
	   libft/ft_lstmap.c \
	   libft/ft_hshnew.c \
	   libft/ft_vecmake.c \
	   libft/ft_vecexpand.c \
	   libft/ft_vecgetptr.c \
	   libft/ft_vecgetptr_dynamic.c \
	   libft/ft_vhmalloc.c \
	   libft/ft_vhmemalloc.c \
	   libft/ft_vhstrdup.c \
	   libft/ft_vlstmap.c \
	   libft/ft_vlstnew.c \
	   libft/ft_vlstpoint.c \
	   libft/ft_vheadnew.c \
	   libft/ft_vheadaddend.c \
	   libft/ft_vheadaddpoint.c \


PRINTF = printf/ft_printf.c \
		printf/ft_dprintf.c \
		printf/parse.c \
		printf/gather_flags.c \
		printf/gather_flags2.c \
		printf/conversions.c \
		printf/format_string.c \
		printf/format_char.c \
		printf/format_decimal.c \
		printf/format_udecimal.c \
		printf/format_percent.c \
		printf/format_pointer.c \
		printf/format_octal.c \
		printf/format_hex.c \
		printf/ft_ptf_itoabase.c \

GNL = get_next_line/get_next_line.c \

SRCS = $(LIBFT) $(GNL) $(PRINTF)

RM = @rm -f

EXE = test

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -fPIC -c $(SRCS)
	@ar rc $(NAME) *.o
	@ranlib $(NAME)
	@echo "\033[33;32mLibft: Ready >:D"

clean:
	$(RM) *.o
	@echo "\033[33mLibft: cleaned..."

fclean: clean
	$(RM) $(NAME)
	@echo "\033[31mLibft: fcleaned..."

re: fclean all
