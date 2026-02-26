# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             #
#    Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo_bonus.c init_bonus.c utils_bonus.c routine_bonus.c monitor_bonus.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
