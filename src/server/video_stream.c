#include "video_stream.h"

/*
Create a video stream struct with the given file name
*/
struct video_stream* create_video_stream(char* filename) {
    FILE *f = fopen(filename, 'rb');
    if (f == NULL) {
        return NULL;
    }

    struct video_stream* stream;
    stream->file = f;
    stream->frame_num = 0;
    return stream;
}

/*
Get the next frame
*/
char* next_frame(struct video_stream *stream) {
    char frame_len_buffer[5], *data_buffer;
    int frame_len;
    fread(frame_len_buffer, sizeof(frame_len_buffer), 1, stream->file);
    frame_len = (int) frame_len_buffer;

    fread(data_buffer, frame_len, 1, stream->file);
    stream->frame_num++;
    return data_buffer;
}