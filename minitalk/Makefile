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

all:
	@gcc -Wall -Wextra -Werror server.c utils.c -o server
	@gcc -Wall -Wextra -Werror client.c utils.c -o client

clean:
	@rm -f server
	@rm -f client

re: clean all

.PHONY:			all clean  re