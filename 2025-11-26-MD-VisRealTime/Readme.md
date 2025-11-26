To allow docker to connect to local display
```sh
xhost +local:docker
```

Build the image
```sh
docker build -t raylib-sim .
```

Run with graphic support
```sh
docker run --rm -it \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    --device /dev/dri:/dev/dri \
    raylib-sim
```

With apptainer
```bash
apptainer run --bind /tmp/.X11-unix --bind /dev/dri raylib-sim.sif
```