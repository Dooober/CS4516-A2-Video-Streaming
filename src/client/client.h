#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <stdio.h>


#include "../enums.h"

struct client {
    enum state state;
    char* server_addr;
    int server_port;
    int rtp_port;
    char* filename;
    int rtsp_seq;
	int session_id;
    int request_sent;
	int teardown_acked;
    int frame_num;
    int sockfd;
};

struct client* create_client(char* server_addr, int server_port, int rtp_port, char* filename);