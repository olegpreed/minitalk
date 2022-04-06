# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: preed <preed@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 18:04:25 by preed             #+#    #+#              #
#    Updated: 2022/04/05 16:55:07 by preed            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER   = server
CLIENT   = client

CC       = gcc
FLAGS    = -Wall -Wextra -Werror

INC      = includes/
SRC_DIR  = src/
OBJ_DIR  = obj/
LIB_DIR  = libft/

HEADER	 = minitalk.h

LIBFT    = libft/libft.a

SRC_C    = client.c 
SRC_S    = server.c
SRC      = $(SRC_C) $(SRC_S)
OBJ_C    = $(addprefix $(OBJ_DIR), $(SRC_C:%.c=%.o)) 
OBJ_S    = $(addprefix $(OBJ_DIR), $(SRC_S:%.c=%.o))
OBJ      = $(OBJ_C) $(OBJ_S)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -o $@ -c $< -I$(INC)

all: makelib $(SERVER) $(CLIENT)

makelib:
	@make -C $(LIB_DIR) bonus --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(SERVER): $(OBJ_DIR) $(OBJ_S) $(INC)$(HEADER) $(LIBFT)
	$(CC) $(FLAGS) -o $(SERVER) $(OBJ_S) -I$(INC) $(LIBFT)

$(CLIENT): $(OBJ_DIR) $(OBJ_C) $(INC)$(HEADER) $(LIBFT)
	$(CC) $(FLAGS) -o $(CLIENT) $(OBJ_C) -I$(INC) $(LIBFT)

clean:
	@make -C $(LIB_DIR) clean --no-print-directory
	rm -rf $(OBJ_DIR) 

fclean: clean
	@make -C $(LIB_DIR) fclean --no-print-directory
	rm -rf $(SERVER) $(CLIENT)

re: fclean
	@make -C $(LIB_DIR) re --no-print-directory
	make all