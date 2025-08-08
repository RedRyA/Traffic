CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJ = main.o graph.o car.o lights.o utils.o
TARGET = traffic

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c graph.h car.h lights.h utils.h
graph.o: graph.c graph.h
car.o: car.c car.h graph.h utils.h
lights.o: lights.c lights.h
utils.o: utils.c utils.h

clean:
	rm -f *.o $(TARGET)