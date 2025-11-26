# Use Ubuntu Development version (currently leads to 25.04 Plucky Puffin)
FROM ubuntu:devel

# 1. Install Build Tools and System Graphics Dependencies
# We need these to compile C++ and for Raylib to interact with X11/OpenGL
RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    tar \
    libgl1-mesa-dev \
    libx11-dev \
    libxcursor-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxi-dev \
    && rm -rf /var/lib/apt/lists/*

# 2. Download Raylib Binaries 
WORKDIR /opt
RUN wget https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz \
    && tar -xzf raylib-5.5_linux_amd64.tar.gz \
    && rm raylib-5.5_linux_amd64.tar.gz

# Define environment variables for paths so we don't have to type them out every time
ENV RAYLIB_PATH="/opt/raylib-5.5_linux_amd64"

# 3. Configure Linker Path (The export LD_LIBRARY_PATH part)
# This ensures ./app finds libraylib.so at runtime
ENV LD_LIBRARY_PATH="$RAYLIB_PATH/lib"

# 4. Setup Project
WORKDIR /app
COPY main.cpp .

# 5. Compile
# -I: Where the headers are (.h)
# -L: Where the libs are (.so/.a)
# -lraylib: The library itself
# -lGL -lm -lpthread ...: Standard system libraries required by Raylib on Linux
RUN g++ main.cpp -o app \
    -I${RAYLIB_PATH}/include \
    -L${RAYLIB_PATH}/lib \
    -lraylib \
    -lGL -lm -lpthread -ldl -lrt -lX11

# Default command to run the app
CMD ["./app"]