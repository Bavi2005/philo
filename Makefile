# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 14:46:02 by bpichyal          #+#    #+#              #
#    Updated: 2025/11/12 17:12:51 by bpichyal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME       = philo

#SRC        = 

OBJ        = $(SRC:.C=o)

CC         = cc
CFLAGS     = -Wall -Wextra -Werror 

all  : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@echo "Bavi's $(NAME) Created"

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@clear
	@echo
	@echo "\033[0;36m╔════════════════════════════════════════════╗\033[0m"
	@echo "\033[0;36m║   ⚠️  SYSTEM PURGE INITIATED — FCLEAN MODE ⚠️   ║\033[0m"
	@echo "\033[0;36m╚════════════════════════════════════════════╝\033[0m"
	@sleep 0.4
	@echo "\033[0;35m[☠] Disconnecting modules... \033[0m"
	@sleep 0.2
	@rm -rf $(NAME)
	@sleep 0.3
	@echo "\033[0;35m[🧹] Removing binaries and executables... \033[0m"
	@$(RM) $(SERVER) $(CLIENT) $(SERVER_B) $(CLIENT_B)
	@sleep 0.3
	@echo "\033[0;31m[⚡] Memory blocks cleared.\033[0m"
	@sleep 0.3
	@echo "\033[1;33m[💾] Temporary cache flushed.\033[0m"
	@sleep 0.3
	@echo "\033[0;32m[✅] All systems reset to factory state.\033[0m"
	@sleep 0.5
	@echo
	@echo "\033[1;36m╔════════════════════════════════════════════╗\033[0m"
	@echo "\033[1;36m║        🔁  CLEANUP SEQUENCE COMPLETE        ║\033[0m"
	@echo "\033[1;36m╚════════════════════════════════════════════╝\033[0m"
	@echo
	@echo "\033[38;5;199m👾   Powered by BAVI | CYBERCORE v2.0\033[0m"
	@echo "\033[38;5;51m🕒   Timestamp: `date +"%H:%M:%S | %d-%m-%Y"`\033[0m"
	@echo "\033[38;5;214m🌌   Status: Environment sanitized and secure\033[0m"
	@echo
	@printf '\a'


re: fclean all
rebonus: fclean bonus

.PHONY: all clean fclean