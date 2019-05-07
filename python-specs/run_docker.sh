#!/bin/bash

docker run --rm -v $(pwd)/../data:/root/data:z -ti $(basename "$PWD")
