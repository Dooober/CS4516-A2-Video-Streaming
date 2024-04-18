# CS4516-A2-Video-Streaming

## Running the code
To run the project you must first install pillow using pip
```pip install pillow```

Then run the server in one command shell
```python server.py {SERVER_PORT}```

Then run the client in another shell
```python client.py 127.0.0.1 {SERVER_PORT} {CLIENT_PORT} movie.Mjpeg```