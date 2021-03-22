# Use the image containing all the tools
FROM ammrat13/gba-base:latest


# Copy the source and build
WORKDIR /gba-lib/src/
COPY src/ .
RUN PREFIX=/gba-lib TARGET=arm-none-eabi- make install

# Copy the auxilary files
WORKDIR /gba-lib/aux-files/
COPY aux-files/ .


# Set the command to build the game
# We assume it's mounted at `/work/`
WORKDIR /work/
CMD [ "make", \
      "PREFIX=/gba-lib/", \
      "HOST=", \
      "TARGET=arm-none-eabi-" ]
