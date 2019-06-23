FROM ubuntu:bionic

SHELL ["/bin/bash", "-o", "pipefail", "-c"]


RUN apt-get update && apt-get install -y --no-install-recommends \
  build-essential \
  pkg-config \
  libc6-dev \
  m4 \
  g++-multilib \
  autoconf \
  libtool \
  ncurses-dev \
  unzip \
  git \
  python \
  python-zmq \
  zlib1g-dev \
  wget \
  curl \
  bsdmainutils \
  automake \
  ca-certificates \
  python-pip \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*


COPY . /arrow
WORKDIR /arrow
# RUN make clean
RUN ./zcutil/build.sh

# RUN ./zcutil/fetch-params.sh
RUN ls /arrow/src

RUN mkdir -p /tmp/bins

RUN cp src/zcashd /tmp/bins/zcashd
RUN cp src/zcash-cli /tmp/bins/zcash-cli
RUN cp src/zcash-tx /tmp/bins/zcash-tx

WORKDIR /
COPY /docker/linux/entrypoint.sh /entrypoint.sh
RUN chmod +x entrypoint.sh

VOLUME /root/home

ENTRYPOINT ["./entrypoint.sh"]

#docker run -it -v /Users/jaysonjacobs/Code/arw/arrow/tmp:/root/home arw
