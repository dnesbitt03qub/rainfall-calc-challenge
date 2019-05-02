#!/bin/bash

for DIR in */ ; do
    [ $DIR == 'data/' ] && continue
    echo $DIR
    cd $DIR
    ./run_docker.sh
    cd ..
done
