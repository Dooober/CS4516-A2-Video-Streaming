#include "rtp_packet.h"

/*
    Encode the RTP packet with header fields and payload
*/
rtp_packet_t* encode(int version, bool padding, bool extension, int cc, short seqnum, bool marker, int pt, long ssrc, char* payload) {
    rtp_packet_t *packet;

    packet->header[0] = (version << 6) + (padding << 5) + (extension << 4) + cc;
    packet->header[1] = (marker << 7) + pt;
    packet->header[2] = (char*) seqnum;
    packet->header[4] = (char*) time(NULL);
    packet->header[8] = (char*) ssrc;
    packet->payload = payload;
    return packet;
}

/*
    Decode the RTP packet
*/
rtp_packet_t* decode(char* byte_stream) {
    rtp_packet_t *packet;
    packet->header[0] = byte_stream;
    packet->payload = byte_stream + HEADER_SIZE;
    return packet;
}

/*
    Return RTP version
*/
int version(rtp_packet_t *packet) {
    return (int) packet->header[0] >> 6;
}

/*
    Return sequence (frame) number
*/
int seq_num(rtp_packet_t *packet) {
    char seq[2] = packet->header[2];
    return (int) seq;
}

/*
    Return timestamp
*/
int timestamp(rtp_packet_t *packet) {
    char timestamp[4] = packet->header[4];
    return (int) timestamp;
}

/*
    Return payload type
*/
int payload_type(rtp_packet_t *packet) {
    return (int) (packet->header[1] << 1) >> 1;
}