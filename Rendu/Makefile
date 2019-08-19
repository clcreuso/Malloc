# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/05/25 17:12:33 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2019/08/19 11:00:25 by clcreuso    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

ifndef $$HOSTTYPE
	@export HOSTTYPE=$(shell uname -m)_$(shell uname -s);
endif

GCC = gcc

FLAGS = -Wall -Wextra -Werror

SHARED_OBJECT = ./libft_malloc_$$HOSTTYPE.so

SYMBOLIC_LINK = ./libft_malloc.so

SOURCE_FOLDER = ./Sources/

INCLUDE_FOLDER = ./Includes/

SOURCE_FILES = show_alloc_mem.c chunk.c free.c tools_02.c malloc.c realloc.c \
			   region.c tools_01.c calloc.c

INCLUDE_FILES = malloc.h

SOURCE_PATH = $(addprefix $(SOURCE_FOLDER), $(SOURCE_FILES))

INCLUDE_PATH = $(addprefix $(INCLUDE_FOLDER), $(INCLUDE_FILES))

OBJ = $(SOURCE_PATH:.c=.o)

all: $(SHARED_OBJECT)

$(SHARED_OBJECT): $(OBJ)
	@$(GCC) -shared -I $(INCLUDE_FOLDER) -o $(SHARED_OBJECT) $(OBJ)
	@rm -rf $(SYMBOLIC_LINK)
	@ln -s $(SHARED_OBJECT) $(SYMBOLIC_LINK)
	@printf "\r\033[0;32m✅️   make $(SHARED_OBJECT) 100%%\033[0m\033[K\n"

./%.o: ./%.c $(INCLUDE_PATH)
	@$(GCC) $(FLAGS) -I $(INCLUDE_FOLDER) -o $@ -c $< 

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(SHARED_OBJECT)
	@rm -rf $(SYMBOLIC_LINK)

re: fclean all