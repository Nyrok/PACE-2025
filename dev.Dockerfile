FROM debian:sid-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    gcc-13 \
    make \
    cmake \
    libc6-dev \
    valgrind \
    vim \
    openjdk-21-jre-headless && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY ds_verifier-1.0.jar /root/ds_verifier-1.0.jar
COPY testall.sh /root/testall.sh

RUN chmod +x /root/testall.sh

CMD ["tail", "-f", "/dev/null"]