# 1. Use the "Slim" variant of Debian (much smaller than 'latest')
FROM debian:bookworm-slim

# 2. Avoid prompts from apt during the build
ENV DEBIAN_FRONTEND=noninteractive

# 3. Update, Install packages, and Clean up in a single layer
#    --no-install-recommends: skips heavy extras (like documentation)
#    rm -rf /var/lib/apt/lists/*: deletes the cache to keep image small
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
	build-essential \
	valgrind \
    vim \
	tree && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# 4. Set the default directory
WORKDIR /app

# 5. Keep the container alive (so it doesn't exit immediately)
CMD ["tail", "-f", "/dev/null"]