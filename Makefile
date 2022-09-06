# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avillar <avillar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:12:34 by thbierne          #+#    #+#              #
#    Updated: 2022/09/02 09:41:40 by avillar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	srcs/main.c				\
		srcs/parsing.c			\
		srcs/init_struct.c		\
		srcs/routine.c			\
		srcs/printing.c			\
		srcs/free_struct.c		\
		srcs/utils/ft_atoi.c	\
		srcs/utils/calcul.c		\
		srcs/utils/ft_putchar.c	\
	
OBJS = $(SRCS:.c=.o)

CC = cc

FSAN = -fsanitize=address

CFLAG = -Wall -Wextra -Werror -g3

all: ${NAME}

.c.o:
	$(CC) $(CFLAG) -c -I/includes/philosopher.h $< -o $@

${NAME}: ${OBJS}
	${CC} -pthread ${OBJS} -o $(NAME)


clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
