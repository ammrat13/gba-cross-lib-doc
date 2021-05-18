# Use the image containing all the tools
FROM ammrat13/gba-base:latest


# Set environment variables for building
# Use a hack to set an empty environment variable:
#  https://github.com/docker/compose/issues/4636
ENV PREFIX=/gba-lib/
ENV HOST=${empty:+empty}
ENV TARGET=arm-none-eabi-
ENV SPECS=-specs=${PREFIX}/aux-files/specs
ENV LNKSCRIPT=-T${PREFIX}/aux-files/lnkscript


# Copy the source and build
WORKDIR ${PREFIX}/src/
COPY src/ .
RUN make install

# Copy the auxilary files
WORKDIR ${PREFIX}/aux-files/
COPY aux-files/ .


# Set the command to build the game
# We assume it's mounted at `/work/`
WORKDIR /work/
CMD make \
    PREFIX=${PREFIX} \
    HOST=${HOST} \
    TARGET=${TARGET} \
    SPECS=${SPECS} \
    LNKSCRIPT=${LNKSCRIPT}
