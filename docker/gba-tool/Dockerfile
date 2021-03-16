# Use Ubuntu for this image
# Alpine doesn't have the required packages
FROM ubuntu:latest

# Make sure the install doesn't prompt us
# See: https://serverfault.com/questions/949991/how-to-install-tzdata-on-a-ubuntu-docker-image
ENV DEBIAN_FRONTEND=noninteractive

# Update the repositories
# Install the toolchain and emulator
RUN apt-get update && \
    apt-get install --yes build-essential check gcc-arm-none-eabi libmgba
