#ifndef __RTP_PACKET_H__
#define __RTP_PACKET_H__

#include <time.h>

#define HEADER_SIZE 12

typedef enum boolean { false, true } bool;

typedef struct rtp_packet {
    char header[HEADER_SIZE];
    char* payload;
} rtp_packet_t;

rtp_packet_t* encode(int version, bool padding, bool extension, int cc, short seqnum, bool marker, int pt, long ssrc, char* payload);
rtp_packet_t* decode(char* byte_stream);
int version(rtp_packet_t *packet);
int seq_num(rtp_packet_t *packet);
int timestamp(rtp_packet_t *packet);
int payload_type(rtp_packet_t *packet);

#endif