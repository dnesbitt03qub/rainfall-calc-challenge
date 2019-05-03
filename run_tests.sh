#!/bin/bash

if [ ! -f data/all.csv ]; then
    wget https://www.0x44.pw/trdc/201905challenge.tar.gz
    tar xvzf 201905challenge.tar.gz
fi

for DIR in */ ; do
    [ $DIR == 'data/' ] && continue
    echo $DIR
    cd $DIR
    ./build_test.sh
    ./run_test.sh
    cd ..
done
