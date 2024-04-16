#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <sys/socket.h>
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

struct client create_client(char* server_addr, int server_port, int rtp_port, char* filename);
void setup_movie(struct client* client);
void exit_client();
void pause_movie(struct client* client);
void play_movie(struct client* client);

#endif