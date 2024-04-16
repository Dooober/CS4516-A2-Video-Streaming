enum state {
    INIT,
    READY,
    PLAYING
};

enum rtsp_request {
    SETUP,
    PLAY,
    PAUSE,
    TEARDOWN
};

enum error_code {
    OK_200,
	FILE_NOT_FOUND_404,
	CON_ERR_500
};