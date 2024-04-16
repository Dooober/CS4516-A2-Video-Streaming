#ifndef __VIDEO_STREAM_H__
#define __VIDEO_STREAM_H__

#include <stdio.h>

struct video_stream {
    FILE *file;
    int frame_num;
};

struct video_stream* create_video_stream(char* filename);
char* next_frame(struct video_stream *stream);

#endif