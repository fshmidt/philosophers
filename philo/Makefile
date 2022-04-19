# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 14:42:52 by mbesan            #+#    #+#              #
#    Updated: 2022/04/19 15:34:23 by mbesan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS		= ./main.c ./exit.c ./init.c ./notifications.c ./threads.c \
			./time.c ./utils.c ./philo.c

OBJS		= $(SRCS:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

HDR			= philo.h

%.o: %.c philo.h Makefile
			$(CC) -g -c $< -o $@

$(NAME):	$(OBJS) $(HDR)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
