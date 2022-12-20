SERVER = server
CLIENT = client
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus
WHITE = \033[0m
BLUE = \033[0;34m
CYAN = \033[0;36m


all: norm $(SERVER) $(CLIENT)

$(SERVER):
	@gcc -Wall -Wextra -Werror server.c -o $(SERVER)
	@echo "$(CYAN)$(SERVER)$(WHITE) is ready to use"

$(CLIENT):
	@gcc -Wall -Wextra -Werror client.c -o $(CLIENT)
	@echo "$(CYAN)$(CLIENT)$(WHITE) is ready to use"

norm:
	@echo "$(BLUE)"
	norminette server.c client.c

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(CLIENT_BONUS):
	@gcc -Wall -Wextra -Werror client_bonus.c -o $(CLIENT_BONUS)
	@echo "$(CYAN)$(CLIENT_BONUS)$(WHITE) is ready to use"

$(SERVER_BONUS):
	@gcc -Wall -Wextra -Werror server_bonus.c -o $(SERVER_BONUS)
	@echo "$(CYAN)$(SERVER_BONUS)$(WHITE) is ready to use"
normb:
	@echo "$(BLUE)"
	norminette server_bonus.c client_bonus.c
clean:
	@rm -rf server client server_bonus client_bonus
	@echo "$(BLUE)Project is clean$(WHITE)"

fclean: clean

re: fclean all

rebonus: fclean bonus