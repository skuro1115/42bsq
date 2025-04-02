# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skatsuya < skatsuya@student.42tokyo.jp>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 22:26:24 by skatsuya          #+#    #+#              #
#    Updated: 2025/04/02 22:48:27 by skatsuya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BSQ Makefile

NAME = bsq
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c output.c solver1.c solver2.c file_reader.c file_reader2.c file_reader3.c bit_utils.c trance_bitmap.c
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
