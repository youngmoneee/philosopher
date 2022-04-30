# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 17:01:04 by youngpar          #+#    #+#              #
#    Updated: 2022/04/29 23:03:33 by youngpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

NAME	= philo

INC		= ./include
DIRS	= ./srcs
SRCF	= main.c \
			exception.c \
			util.c \
			init.c \
			mutex.c \
			philosopher.c

SRCS	= $(addprefix $(DIRS)/, $(SRCF))
OBJS	= $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -lpthread -I $(INC) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean:		clean
	@rm -rf $(NAME)

re:			fclean all

.PHONY: $(NAME) all clean fclean re
