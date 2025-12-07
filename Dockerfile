# 1. Use the "Slim" variant of Debian (much smaller than 'latest')
FROM debian:sid-slim

# 2. Avoid prompts from apt during the build
ENV DEBIAN_FRONTEND=noninteractive

# 3. Update, Install packages, and Clean up in a single layer
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    # Explicitly install GCC 13 and 'make'
    gcc-13 \
    make \
    # Install the static C library headers (CRUCIAL for -static linking)
    libc6-dev \
    valgrind \
    vim \
    tree \
    openjdk-21-jre-headless && \
    # Set gcc-13 as the default 'gcc' command
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# 4. Set the default directory
WORKDIR /app

COPY ds_verifier-1.0.jar /root/ds_verifier-1.0.jar
COPY testall.sh /root/testall.sh

RUN chmod +x /root/testall.sh

RUN ls -la .

# 5. Keep the container alive (so it doesn't exit immediately)
CMD ["tail", "-f", "/dev/null"]