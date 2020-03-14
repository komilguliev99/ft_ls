# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/08 15:33:43 by dcapers           #+#    #+#              #
#    Updated: 2020/03/14 15:56:46 by dcapers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

DIRS		= src/

LIST		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c     \
				ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c      \
				ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c   \
				ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c   \
				ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c    \
				ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
				ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c   \
				ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c    \
				ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c   \
				ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c             \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c        \
				ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c  \
				ft_isspace.c ft_strissorted.c ft_lstnth.c ft_strcntif.c          \
				ft_lstprint.c ft_itoa_base.c ft_uitoa_base.c ft_strjoin_by.c	 \
				ft_pow.c ft_ctos.c ft_putchar_cnt.c get_next_line.c ft_utils.c   \
				ft_printf.c handle_char.c handle_di.c handle_float.c handle_o.c  \
				handle_point.c handle_string.c handle_u.c handle_x.c set_float.c \
				set_argument.c set_arglen.c set_format.c initialize_state.c      \
				ft_gmtime.c

SOURCE	=	$(addprefix $(DIRS), $(LIST))
OBJ		=	$(patsubst %.c,%.o,$(SOURCE))
INCLUDES	= includes/

FLAGS ?= -Wall -Wextra -Werror

all: $(OBJ) $(NAME)

%.o: %.c
	gcc $(FLAGS) -I $(INCLUDES) -c $< -o $@ -MD

$(NAME): $(OBJ)
	ar rc $(NAME) $?
	ranlib $(NAME)

clean:
	rm -f $(OBJ) $(wildcard $(addsuffix *.d,$(DIRS)))

fclean: clean
	rm -f $(NAME)

re: fclean all

include $(wildcard $(addsuffix *.d,$(DIRS)))

.PHONY: all clean fclean re
