all: server client

server: server/server.c
	gcc server/server.c -o out/server

client: client/client.c
	gcc client/client.c -o out/client -lSDL2 -lGL -lm -lGLU