# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/28 10:35:35 by ratavare          #+#    #+#              #
#    Updated: 2023/07/11 16:16:50 by ratavare         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		philo

CC			=		cc

CFLAGS		=		-Wall -Wextra -Werror -g

INCLUDES	=		-I$(HEADERS_DIRECTORY)

HEADERS_DIRECTORY = ./includes/

RM			=		rm -f

SRC 		=		srcs/*.c

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) $(CFLAGS) $(SRC) $(INCLUDES) -o $(NAME)

clean:		
			make clean -C ./libft
			$(RM) $(NAME)
fclean:
			make fclean -C ./libft
			$(RM) $(NAME)

re:		fclean	$(NAME)

bonus:		$(BONUS)

$(BONUS):	$(LIBFT) $(FT_PRINTF) $(SRCB)
			$(CC) $(CFLAGS) $(SRCB) $(FT_PRINTF) $(LIBFT) $(INCLUDES) -I /checker/checker.h -o $(BONUS)
			