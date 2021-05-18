# Use Alpine for this image
# We need edge since it has the required packages
FROM alpine:3.13


# Install build packages
RUN apk add --no-cache make gcc g++ libc-dev cmocka-dev
# Install the cross compiler
# Need unstable repositories for this
RUN apk add --no-cache --repository https://dl-cdn.alpinelinux.org/alpine/edge/community gcc-arm-none-eabi

# Install mGBA
# Not in the repositories, so have to do manually
RUN \
    # Change to the build directory
    mkdir -pv /usr/src && cd /usr/src && \
    # Install build dependencies
    apk add --no-cache cmake git && \
    # Do the build
    git clone --branch 0.8.4 --depth 1 https://github.com/mgba-emu/mgba.git && \
    cd mgba && mkdir build && cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DDISTBUILD=ON -DLIBMGBA_ONLY=ON -DM_CORE_GB=OFF .. && \
    make && make install && \
    # Cleanup the build
    cd ../.. && rm -rfv mgba && \
    # Remove build dependencies
    apk del --no-cache cmake git


# Set the working directory
WORKDIR /
