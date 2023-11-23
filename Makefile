# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 10:35:35 by ratavare          #+#    #+#              #
#    Updated: 2023/11/23 20:06:49 by ratavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		philo

CC			=		cc

CFLAGS		=		-Wall -Wextra -Werror -pthread -g -fsanitize=thread

INCLUDES	=		-I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY = ./includes/

RM			=		rm -f

SRC 		=		srcs/*.c

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) $(CFLAGS) $(SRC) $(INCLUDES) -o $(NAME)

clean:		
			$(RM) $(NAME)
fclean:
			$(RM) $(NAME)

re:			fclean $(NAME)

v:
			make && valgrind ./philo