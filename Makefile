# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 11:31:41 by dcapers           #+#    #+#              #
#    Updated: 2020/03/14 16:56:50 by dcapers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIST	=	 main.c create_state.c parsing.c ft_filesort.c create_file.c   	\
			ft_strsort.c fill_data_for.c handle_lsflags.c sort_callbacks.c  \
			time_cmp.c print_ls_format.c ft_strmode.c print_ff_format.c     \
			create_lst.c set_flags.c set_date.c set_mode.c sort_callbacks2.c\

DIRS	=	src/
SOURCE	=	$(addprefix $(DIRS), $(LIST))
OBJ		=	$(patsubst %.c,%.o,$(SOURCE))

LIB		= libft/libft.a
LDIRS	= libft/ 

LIB_ALL		= $(addsuffix .all,$(LDIRS))
LIB_CLEAN	= $(addsuffix .clean,$(LDIRS))
LIB_FCLEAN	= $(addsuffix .fclean,$(LDIRS))

INCS		= includes/
INCS_LIBFT	= $(addsuffix includes/,$(LDIRS))

FLAGS ?= -Wall -Wextra -Werror

all: $(LIB_ALL) $(NAME)

clean: $(LIB_CLEAN)
	rm -f $(OBJ) $(wildcard $(addsuffix *.d,$(DIRS)))

fclean: $(LIB_FCLEAN) clean
	rm -f $(NAME)

re:		fclean all

%.o: %.c
	gcc $(FLAGS) -c $< -o $@ -I $(INCS_LIBFT) -I $(INCS) -MD

$(NAME): $(OBJ) $(LIB)
	gcc $(FLAGS) $(OBJ) -o $(basename $(NAME)) $(LIB)

%.all:
	make -C $*

%.clean:
	make -C $* clean

%.fclean:
	rm -f $(addsuffix *.a,$*)

include $(wildcard $(addsuffix *.d,$(DIRS)))

.PHONY: all clean fclean re
