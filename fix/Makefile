# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 22:26:24 by skatsuya          #+#    #+#              #
#    Updated: 2025/04/02 21:04:18 by skatsuya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BSQ Makefile

NAME = bsq
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c parser_utils.c file_utils.c parser.c reader.c solver.c solver2.c utility.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
