# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonshin <yonshin@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 09:01:06 by yonshin           #+#    #+#              #
#    Updated: 2022/11/17 02:03:14 by yonshin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
CFLAGS = -Wall -Wextra -Werror
LIB = ./lib/libft.a
INCLUDE = -I$(dir $(LIB))
SERVER_OBJS = \
	server.o

CLIENT_OBJS = \
	client.o

	
all: $(SERVER) $(CLIENT)

bonus: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJS) $(LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIB) $(DEBUG) $(OUTPUT_OPTION)

$(CLIENT): $(CLIENT_OBJS) $(LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIB) $(DEBUG) $(OUTPUT_OPTION)

$(LIB):
	make -C $(@D)

%.o: %.c $(LIB)
	$(CC) $(CFLAGS) $(OUTPUT_OPTION) $(INCLUDE) $(DEBUG) -c $*.c

clean:
	rm -f $(SERVER_OBJS)
	rm -f $(CLIENT_OBJS)

fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)

re: 
	make fclean
	make all

debug:
	make DEBUG='-g3 -fsanitize=address'

.PHONY : all clean fclean re bonus debug
