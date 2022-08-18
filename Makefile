CXX = gcc
CFLAGS = -LGLFW -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm -I./ -std=c99 -Wall -Wextra
DEPS = glad/glad.h shader.h stb_image.h
OBJ = main.o

%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< -g $(CFLAGS)

Hexerei: $(OBJ)
	$(CXX) -o $@ $^ glad/glad.c -g $(CFLAGS)

clean:
	rm Hexerei main.o
