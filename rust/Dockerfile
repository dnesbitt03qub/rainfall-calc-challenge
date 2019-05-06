FROM alpine

WORKDIR /home
RUN mkdir /data

# ----------------------------------
# Put dependancies here...
RUN apk update && apk add \
    bash \
    rust \
    cargo

COPY . /home

# ----------------------------------
# Put build command (if any) in this script...
RUN sh /home/build_test.sh

ENTRYPOINT sh /home/run_test.sh