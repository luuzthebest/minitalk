CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

H_FILE = minitalk.h

UTILS = utils.c
SERVER_SRC = server.c
CLIENT_SRC = client.c
B_SERVER_SRC = server_bonus.c
B_CLIENT_SRC = client_bonus.c

UTILS_OBJ = $(UTILS:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
B_SERVER_OBJ = $(B_SERVER_SRC:.c=.o)
B_CLIENT_OBJ = $(B_CLIENT_SRC:.c=.o)

SERVER = server
CLIENT = client
B_SERVER = bonus_server
B_CLIENT = bonus_client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(CLIENT): $(CLIENT_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(B_SERVER): $(B_SERVER_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(B_CLIENT): $(B_CLIENT_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(H_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(B_CLIENT) $(B_SERVER)

clean:
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ) $(B_SERVER_OBJ) $(B_CLIENT_OBJ) $(UTILS_OBJ)

fclean: clean
	$(RM) $(SERVER) $(CLIENT) $(B_SERVER) $(B_CLIENT)

re: fclean all

.PHONY: all clean fclean re bonus