#!/bin/bash

docker run --rm -v $(pwd)/../data:/data:z -ti $(basename "$PWD")
