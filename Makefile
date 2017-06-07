all:
	gcc src/*.c src/WebInterface/*.c -lpthread  -o Test
clean:
	rm Test
