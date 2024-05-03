#!/bin/bash

## Use Git Bash to run this script

set -e

SCRIPT_DIR=$(cd $(dirname $0); pwd)
PROJECT_DIR=$(cd $SCRIPT_DIR/..; pwd)

echo "*****Building godot-cpp for Windows in $PROJECT_DIR*****"

bash $SCRIPT_DIR/build.sh windows
