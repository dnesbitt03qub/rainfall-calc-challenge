FROM alpine:3.9

WORKDIR /root
RUN mkdir /root/data

# ----------------------------------
# Put dependancies here...
RUN apk update && apk add \
    bash \
    python3 \
    python3-dev

ADD . /root/specs/
WORKDIR /root/specs

# ----------------------------------
# Put build command (if any) in this script...
RUN sh /root/specs/build_test.sh

ENTRYPOINT sh /root/specs/run_test.sh
