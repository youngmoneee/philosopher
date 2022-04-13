# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 16:35:43 by youngpar          #+#    #+#              #
#    Updated: 2022/04/13 17:21:42 by youngpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
BNAME	= philo_bonus

all:	$(NAME)

$(NAME):
	@make -C ./philo
	@mv ./philo	.

$(BNAME):
	@make -C ./philo_bonus
	@mv ./philo_bonus .

clean:
	@make -C $(NAME) clean
	@make -C $(BNAME) clean

fclean:
	@make -C $(NAME) fclean
	@make -C $(BNAME) fclean

re:	fclean all

.PHONY: $(NAME) $(BNAME) all re clean fclean
