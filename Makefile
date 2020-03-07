# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcapers <dcapers@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 11:31:41 by dcapers           #+#    #+#              #
#    Updated: 2020/03/07 16:20:17 by dcapers          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = clang

NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

DIR_S = src

DIR_O = objects

HEADER = includes

HEADERS = includes/*.h

SOURCES = main.c create_state.c parsing.c ft_filesort.c create_file.c   	\
			ft_strsort.c fill_data_for.c handle_lsflags.c sort_callbacks.c  \
			time_cmp.c long_format.c ft_strmode.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	make -C $(LIBFT)
	cp libft/libft.a ./
	gcc $(FLAGS) -I $(HEADER) $(OBJS) libft.a -o $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p objects
	gcc $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	rm -f $(OBJS)
	rm -rf $(DIR_O)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	make fclean -C $(LIBFT)

re: fclean all
