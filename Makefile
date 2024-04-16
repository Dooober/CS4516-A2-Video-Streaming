all: server client

server: src/server/server.c	
	gcc src/server/server.c src/server/server_worker.c -o out/server

client: src/client/client_launcher.c
	gcc -g src/client/client_launcher.c src/client/client.c -o out/client -lSDL2 -lGL -lm -lGLU

clean:
	rm -rf *o out/client out/server