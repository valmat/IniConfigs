CC 	 = clang++
#CC 	 = g++

NAME	 = main
CFLAGS	 = -std=c++11 -O0 -g -Wall 
BINFILE  = $(NAME).bin

all: ${BINFILE}

$(NAME).o: $(NAME).cpp
	$(CC) $(NAME).cpp -I. -I../include $(CFLAGS) -c -o $(NAME).o


${BINFILE}: $(NAME).o
	$(CC) $(NAME).o ../src/libiniconfig.a $(CFLAGS) -o $(NAME).bin
	#$(CC) $(NAME).o /usr/local/lib/libiniconfig.a $(CFLAGS) -o $(NAME).bin
	@echo
	@echo "\033[1;36mBuild complite \033[0m"

.PHONY: withshared
withshared: $(NAME).o
	$(CC) $(NAME).o -L../src -L/usr/local/lib -liniconfig $(CFLAGS) -o $(NAME).bin
	@echo
	@echo "\033[5;36mBuild complite \033[0m"

	
run:
	./$(NAME).bin

clean:
	rm -f $(NAME).o $(NAME).bin


