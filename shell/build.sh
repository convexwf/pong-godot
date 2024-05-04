#!/bin/bash

# This script is used to build the project.
## Usage: ./build.sh [windows|linux]

BUILD_PLATFORM=$1
GODOT_CPP_VERSION=4.2

if [ -z "$BUILD_PLATFORM" ]; then
    echo "Usage: $0 [windows|linux]"
    exit 1
fi

if [ "$BUILD_PLATFORM" != "windows" ] && [ "$BUILD_PLATFORM" != "linux" ]; then
    echo "Error: BUILD_PLATFORM must be 'windows' or 'linux'"
    exit 1
fi

set -e

SCRIPT_DIR=$(cd $(dirname $0); pwd)
PROJECT_DIR=$(cd $SCRIPT_DIR/..; pwd)

echo "Building project in $PROJECT_DIR"

# Check if the godot-cpp repository exists, if not, clone it
if [ ! -d $PROJECT_DIR/godot-cpp ]; then
    echo "Cloning godot-cpp repository"
    git clone -b ${GODOT_CPP_VERSION} git@github.com:godotengine/godot-cpp.git $PROJECT_DIR/godot-cpp
fi
cd $PROJECT_DIR/godot-cpp && git pull origin ${GODOT_CPP_VERSION}

# Try to pull the docker image first, if it fails, build it
docker pull convexwf/godot-gdextension-cpp-builder || \
    cd $PROJECT_DIR && docker build -t convexwf/godot-gdextension-cpp-builder .

# Check if we are running on Windows, if so, we need to add a slash to the project directory
AUTO_SLASH=""
if [ "$BUILD_PLATFORM" == "windows" ]; then
    AUTO_SLASH="/"
fi

docker run --rm \
    -v ${AUTO_SLASH}${PROJECT_DIR}:/app \
    convexwf/godot-gdextension-cpp-builder \
    bash -c "cd /app/ && source activate gde && scons platform=${BUILD_PLATFORM}"
