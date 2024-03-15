# Name of the executable
NAME = pipex

# Compiler
CC = gcc 
# Compiler flags
CFLAGS := -Wall -Wextra -Werror -g -Iheaders/ 
# Include paths for header files

# Library pathse
LDFLAGS := -Lprintf -Lgnl

# Libraries to link against, including the math library if needed
#LDLIBS := -lft -lftprintf

# Source files
SRC = $(wildcard *.c) \
		$(wildcard printf/ft_*.c) \
		$(wildcard gnl/ft_*.c) \
		$(wildcard functions/ft_*.c) \
	  
# SRC := $(wildcard src/*.c)
# Object files
OBJ = $(SRC:.c=.o)

# Phony targets for make commands
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Rule to link the program
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

#
# Rule to clean object files and other temporary files
clean:
	rm -f $(OBJ) $(NAME)

# Rule to fully clean the project, including the executable
fclean: clean
	rm -f $(NAME)

# Rule to re-make the project
re: fclean all
