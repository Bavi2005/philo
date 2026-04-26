# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#              #
#    Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

SRC			= main.c \
			  parse.c \
			  utils.c \
			  init.c \
			  init_setup.c \
			  process.c \
			  child.c \
			  routine.c \
			  routine_utils.c \
			  monitor.c \
			  print.c

OBJ			= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re