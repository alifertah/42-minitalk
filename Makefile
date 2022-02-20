
CFLAGS = -Wall -Werror -Wextra
CC = cc
CLIENT = client
SERVER = server

all: $(CLIENT) $(SERVER)

$(CLIENT) :
		$(CC) $(CFLAGS) client.c utilise.c -o client
$(SERVER) :
		$(CC) $(CFLAGS) server.c utilise.c -o server

clean:
	rm -rf $(CLIENT) $(SERVER)

fclean:
	rm -rf $(CLIENT) $(SERVER)

re: fclean all