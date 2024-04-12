#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: server [PORT]\n");
        return -1;
    }
    int port = atoi(argv[1]);

    printf("PORT=%d\n", port);

    return 0;
}

