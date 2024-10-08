#!/bin/bash

# remove exited containers
docker container prune -f
# remove all images tagged with <none>
docker rmi $(docker images -f "dangling=true" -q)

# remove all images
# docker rmi $(docker images -q)
