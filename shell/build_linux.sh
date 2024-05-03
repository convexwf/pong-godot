#!/bin/bash

set -e

SCRIPT_DIR=$(cd $(dirname $0); pwd)
PROJECT_DIR=$(cd $SCRIPT_DIR/..; pwd)

echo "*****Building godot-cpp for Linux in $PROJECT_DIR*****"

bash $SCRIPT_DIR/build.sh linux
