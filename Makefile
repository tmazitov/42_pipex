# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmazitov <tmazitov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/27 21:27:48 by tmazitov          #+#    #+#              #
#    Updated: 2023/08/27 21:27:49 by tmazitov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP
NAME		=	pipex
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

#FILES AND PATH
CHAN_SRCS	=	chan/chan.c \
				chan/close.c \
				chan/free.c \
				chan/payload.c  
CHAN_OBJ	=	$(CHAN_SRCS:.c=.o)

GNL_SRCS	=	get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c
GNL_OBJ	=	$(GNL_SRCS:.c=.o)

SRC_SRCS	=	src/com_exec.c \
				src/com_queue_node.c \
				src/com_queue_utils.c \
				src/com_queue.c \
				src/pipex.c \
SRC_OBJ		=	$(SRC_SRCS:.c=.o)

UTILS_SRCS	=	utils/utils.c \
				utils/find_command.c \
				utils/ft_split.c
UTILS_OBJ	=	$(UTILS_SRCS:.c=.o)

HEADER		=	src/pipex.h \
				chan/chan.h \
				utils/utils.h \
				get_next_line/get_next_line.h \


#COMMANDS
%.o: %.c $(HEADER) Makefile
	@${CC} ${FLAGS} -c $< -o $@

$(NAME): $(UTILS_OBJ) $(GNL_OBJ) $(CHAN_OBJ) $(SRC_OBJ)
	@$(CC) $(UTILS_OBJ) $(GNL_OBJ) $(CHAN_OBJ) $(SRC_OBJ) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

all: $(NAME)

bonus: $(UTILS_OBJ) $(GNL_OBJ) $(CHAN_OBJ) $(SRC_OBJ)
	@$(CC) $(UTILS_OBJ) $(GNL_OBJ) $(CHAN_OBJ) $(SRC_OBJ) -o $(NAME)
	@echo -e "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@$(RM) $(UTILS_OBJ)
	@$(RM) $(GNL_OBJ)
	@$(RM) $(CHAN_OBJ)
	@$(RM) $(SRC_OBJ)
	@echo -e "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:	clean
	@$(RM) $(NAME)
	@echo -e "$(RED)all deleted!$(DEFAULT)"

re: fclean all

.PHONY:		all clean fclean bonus re

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
