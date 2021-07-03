FROM debian:buster-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    curl \
    git \
    gcc \
    gdb \
    g++ \
    make \
    libxft-dev \
    libxpm-dev \
    locales \
    unzip \
    vim \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN git config --global core.filemode false

# Set the locale
RUN sed -i 's/# \(en_US\.UTF-8 .*\)/\1/' /etc/locale.gen && \
    locale-gen
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8  

WORKDIR /workspaces/tyupro/

RUN curl -O http://www.arch.info.mie-u.ac.jp/~sasaki/hobby/software/EzGraph-master.zip && \
    unzip EzGraph-master.zip && \
    rm EzGraph-master.zip

WORKDIR /workspaces/tyupro/EzGraph-master

RUN rm ./config.guess && \
    curl "http://git.savannah.gnu.org/gitweb/?p=config.git;a=blob_plain;f=config.guess;hb=HEAD" -o config.guess

RUN ./configure; make; make install

RUN echo "/usr/local/lib" > /etc/ld.so.conf.d/usr-local-lib.conf && ldconfig -v

ENV DISPLAY host.docker.internal:0.0

ENV TZ "Asia/Tokyo"
