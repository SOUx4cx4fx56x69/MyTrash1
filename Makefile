all:
	gcc main.c socket.c stratum.c base64.c util.c json.c -lpthread  -o Test
