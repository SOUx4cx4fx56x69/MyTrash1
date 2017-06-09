all:
	gcc src/*.c src/*/*.c -lpthread -o Test
clean:
	rm Test
