#ifndef __SERVER_WORKER_H__
#define __SERVER_WORKER_H__

struct client_info {
    int sockfd;
};

struct server_worker {
    struct client_info *c_info;
};

void server_worker_run(struct client_info *c_info);

#endif