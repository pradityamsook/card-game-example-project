#!/bin/bash

WATCH_DIR="/app/."
BUILD_DIR="/app/build"
while inotifywait -e modify -e create -e delete -r "$WATCH_DIR"; do
    echo "File change detected. Rebuilding..."
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir -p "$BUILD_DIR"
    fi
    cmake ..
    make -j$(nproc)
    cd ..
    echo "Rebuild complete."
done
