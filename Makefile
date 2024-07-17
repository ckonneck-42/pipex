# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckonneck <ckonneck@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 18:09:26 by ckonneck          #+#    #+#              #
#    Updated: 2024/07/17 16:11:35 by ckonneck         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)
LIBFT_DIR = ./libft
LIBS = -L$(LIBFT_DIR) -lft

# Source files for pushswap
PIPEX_SRCS = pipex.c pipex_utils.c
PIPEX_OBJS = $(PIPEX_SRCS:.c=.o)

# 'all' target
all: $(NAME)

$(NAME): libft $(PIPEX_OBJS)
	$(CC) $(CFLAGS) $(PIPEX_OBJS) $(LIBS) -o $(NAME)

# Compile libft
libft:
	$(MAKE) -C $(LIBFT_DIR)

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 'clean' rule
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(PIPEX_OBJS)

# 'fclean' rule
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# 're' rule
re: fclean all

# Declare phony targets
.PHONY: all libft clean fclean re