# Use the image containing all the tools
FROM ammrat13/gba-base:latest

# Start the working directory in `/`
WORKDIR /


# Copy the source and build
WORKDIR /gba-lib/src/
COPY src/ .
RUN PREFIX=/gba-lib TARGET=arm-none-eabi- make install

# Copy the tests
# Needed because CI doesn't support volume mounting
# Don't build or run at this point - we leave that to CI
WORKDIR /gba-lib/tests/
COPY tests/ .

# Copy the auxilary files
WORKDIR /gba-lib/aux-files/
COPY aux-files/ .


# Set the command to build the game
# We assume it's mounted at `/work/`
WORKDIR /work/
CMD [ "make", \
      "PREFIX=/gba-lib/", \
      "HOST=x86_64-linux-gnu-", \
      "TARGET=arm-none-eabi-" ]
