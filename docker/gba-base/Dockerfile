# Use Alpine for this image
# We need edge since it has the required packages
FROM alpine:edge


# Install the toolchain
# Use the testing repository for `gcc-arm-none-eabi`
RUN echo "https://dl-cdn.alpinelinux.org/alpine/edge/testing" >> /etc/apk/repositories && \
    apk add --no-cache make gcc g++ libc-dev gcc-arm-none-eabi check-dev

# Install mGBA
# Not in the repositories, so have to do manually
    # Change to the build directory
RUN mkdir -pv /usr/src && cd /usr/src && \
    # Install build dependencies
    apk add --no-cache cmake git && \
    # Do the build
    git clone https://github.com/mgba-emu/mgba.git && \
    cd mgba && git checkout 0.8.4 && \
    mkdir build && cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DLIBMGBA_ONLY=ON -DM_CORE_GB=OFF .. && \
    make && make install && \
    # Cleanup the build
    cd ../.. && rm -rfv mgba && \
    # Remove build dependencies
    apk del --no-cache cmake git


# Set the working directory
WORKDIR /
