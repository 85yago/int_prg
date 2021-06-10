FROM debian:buster-slim

RUN apt update && apt install -y \
    git \
    gcc \
    gdb \
    g++ \
    vim \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN git config --global core.filemode false

ENV TZ="Asia/Tokyo"
