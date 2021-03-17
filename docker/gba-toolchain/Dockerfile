# Use the image containing all the tools
FROM ammrat13/gba-base:latest

# Start the working directory in `/`
WORKDIR /


# Copy the source and build
WORKDIR /gba-lib/src/
COPY src/ .
RUN PREFIX=/gba-lib TARGET=arm-none-eabi make install

# Copy the auxilary files
WORKDIR /gba-lib/aux-files
COPY aux-files/ .


# Set the command to build the game
# We assume it's mounted at `/game/`
WORKDIR /game/
CMD [ "make", \
      "PREFIX=/gba-lib", \
      "TARGET=arm-none-eabi", \
      "CC=arm-none-eabi-gcc -specs=/gba-lib/aux-files/specs -T/gba-lib/aux-files/lnkscript" ]
