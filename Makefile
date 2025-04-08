CC = cc -Wall -Wextra -Werror

RM = rm -rf

H_FILE = minitalk.h

SERVER_SRC = server.c
CLIENT_SRC = client.c

B_SERVER_SRC = server_bonus.c
B_CLIENT_SRC = client_bonus.c

SERVER_OBJ = server.o
CLIENT_OBJ = client.o

B_SERVER_OBJ = server_bonus.o
B_CLIENT_OBJ = client_bonus.o

SERVER = server
CLIENT = client

B_SERVER = bonus_server
B_CLIENT = bonus_client
all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(H_FILE)
	$(CC) $< -o $@
$(CLIENT): $(CLIENT_OBJ) $(H_FILE)
	$(CC) $< -o $@

$(B_SERVER): $(B_SERVER_OBJ) $(H_FILE)
	$(CC) $< -o $@
$(B_CLIENT): $(B_CLIENT_OBJ) $(H_FILE)
	$(CC) $< -o $@

.%o: .%c
	$(CC) -c $< -o $@

bonus: $(B_CLIENT) $(B_SERVER)

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(B_CLIENT_OBJ) $(B_SERVER_OBJ)

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(B_CLIENT) $(B_SERVER)

re: fclean all

.PHONY: all clean fclean re