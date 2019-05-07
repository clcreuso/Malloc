# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/05/25 17:12:33 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/05/25 17:12:33 by clcreuso    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

GCC = gcc

FLAGS = -Wall -Wextra -Werror

SHARED_OBJECT = ./libft_malloc_$$HOSTTYPE.so

SYMBOLIC_LINK = ./libft_malloc.so

INCLUDE_FOLDER = ./Includes/

INCLUDE_FILES = malloc.h

INCLUDE_PATHES = $(addprefix $(INCLUDE_FOLDER), $(INCLUDE_FILES))
		
SOURCE_FOLDER = ./Sources/

SOURCE_FILES = main.c

SOURCE_PATHES = $(addprefix $(SOURCE_FOLDER), $(SOURCE_FILES))

OBJ =	$(SOURCE_PATHES:.c=.o)

all: $(SYMBOLIC_LINK)

$(SYMBOLIC_LINK): $(OBJ)
ifndef $$HOSTTYPE
	@export HOSTTYPE=$(shell uname -m)_$(shell uname -s);
endif
	@ar rcs $(SHARED_OBJECT) $(OBJ)
	@ln -s $(SHARED_OBJECT) $(SYMBOLIC_LINK)
	@printf "\r\033[0;32mmake $(SYMBOLIC_LINK)\033[0m\033[K\n"

./%.o: ./%.c $(INCLUDE_PATHES)
	@$(GCC) $(FLAGS) -I $(INCLUDE_FOLDER) -o $@ -c $< 

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(SHARED_OBJECT)
	@rm -rf $(SYMBOLIC_LINK)

re: fclean all