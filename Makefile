# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msimoes- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/09 18:08:31 by msimoes-          #+#    #+#              #
#    Updated: 2022/04/28 21:42:00 by msimoes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_SERVER	= server.c

OBJ_SERVER	= $(SRC_SERVER:.c=.o)

SRC_CLIENT	= client.c

OBJ_CLIENT	= $(SRC_CLIENT:.c=.o)

SRC_UTILS	= utils.c

OBJ_UTILS	= $(SRC_UTILS:.c=.o)


CC		= gcc

CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address

SERVER_NAME	= server

CLIENT_NAME	= client

all: $(SERVER_NAME) $(CLIENT_NAME)

server: $(OBJ_SERVER) $(OBJ_UTILS)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_UTILS) -o $(SERVER_NAME)

client:	$(OBJ_CLIENT) $(OBJ_UTILS) 
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(OBJ_UTILS) -o $(CLIENT_NAME)

clean:
	rm -rf *.o

fclean:	clean
	rm -rf $(SERVER_NAME) $(CLIENT_NAME)

re:	fclean all

.PHONY: all clean fclean re
