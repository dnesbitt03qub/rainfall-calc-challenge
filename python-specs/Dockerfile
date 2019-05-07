FROM alpine:3.9

WORKDIR /root
RUN mkdir /root/data

# ----------------------------------
# Put dependancies here...
RUN apk update && apk add \
    bash \
    python3 \
    python3-dev

COPY . /root

# ----------------------------------
# Put build command (if any) in this script...
RUN sh /root/build_test.sh

ENTRYPOINT sh /root/run_test.sh