.PHONY: main
all: main

clean:
	rm -rf *.o main

.PHONY: main
main:
	g++ -Wall -Wextra -o main main.cpp -lsfml-graphics -lsfml-window -lsfml-system