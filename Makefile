CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm

OpenGLEngine: src/main.cpp src/glad.c src/stb_image.cpp
	g++ $(CFLAGS) -Iinclude -o OpenGLEngine src/main.cpp src/glad.c src/stb_image.cpp $(LDFLAGS)
