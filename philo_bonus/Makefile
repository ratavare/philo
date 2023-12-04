# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 10:35:35 by ratavare          #+#    #+#              #
#    Updated: 2023/12/04 22:36:01 by ratavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		philo_bonus

CC			=		cc

CFLAGS		=		-Wall -Wextra -Werror -pthread -g #-fsanitize=address

INCLUDES	=		-I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY = ./includes/

RM			=		rm -f

SRC 		=		srcs/check.c srcs/init.c srcs/main.c srcs/philo.c srcs/time.c srcs/utils.c srcs/utils2.c

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) $(CFLAGS) $(SRC) $(INCLUDES) -o $(NAME)

clean:		
			$(RM) $(NAME)
fclean:
			$(RM) $(NAME)

re:			fclean $(NAME)
