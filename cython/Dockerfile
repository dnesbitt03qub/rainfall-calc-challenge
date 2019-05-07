FROM alpine

WORKDIR /home
RUN mkdir /data

# ----------------------------------
# Put dependancies here...
RUN apk update && apk add \
    bash \
    python3 \
    python3-dev \
    build-base

RUN pip3 install cython
    

COPY . /home

# ----------------------------------
# Put build command (if any) in this script...
RUN sh /home/build_test.sh

ENTRYPOINT sh /home/run_test.sh