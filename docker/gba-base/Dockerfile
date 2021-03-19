# Use Ubuntu for this image
# Alpine doesn't have the required packages
FROM ubuntu:latest

# Start the working directory in `/`
WORKDIR /

# Make sure the install doesn't prompt us
# See: https://serverfault.com/questions/949991/how-to-install-tzdata-on-a-ubuntu-docker-image
ENV DEBIAN_FRONTEND=noninteractive


# Update the repositories
# Install the toolchain and emulator dependencies
# Tap to XUnit needed for testing
RUN apt-get update && \
    apt-get install --yes build-essential gcc-arm-none-eabi check git cmake

# Install mGBA
# Not in the repositories, so have to do manually
WORKDIR /usr/src/
RUN git clone https://github.com/mgba-emu/mgba.git && \
    cd mgba && git checkout 0.8.4 && \
    mkdir build && cd build && \
    cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DLIBMGBA_ONLY=on -DM_CORE_GB=OFF .. && \
    make && make install


# Reset the working directory
WORKDIR /
