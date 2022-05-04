TARGET = philo #Delante $(BINARY) para gestión de salida de binarios
OBJ_DIR = ../Obj 
#BINARY = ../Bin
SRC_DIR = .
OBJS =	philosophers.o \
		time_management.o \
		init_manager.o \
		utils.o	\
		philo_does.o
COMPILER = gcc
CFLAFS = -Wall -Wextra -Werror -g -fsanitize=address -g3 -pthread -I philo.h 
#INCDIR AÑADIR

$(TARGET) : $(OBJS)
	@$(COMPILER) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o : $(SRC_DIR)/%.c
	@$(COMPILER) -c $(CFLAGS) $< -o $@
#mkdir -p $(OBJ_DIR)
all: $(TARGET) $(OBJS) $(INC)
re: fclean all
clean :
	@rm -r *.o $(TARGET)
fclean :
	@rm -r *.o $(TARGET)
.PHONY: clean re fclean