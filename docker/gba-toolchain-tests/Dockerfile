# Start with our toolchain image
FROM ammrat13/gba-toolchain:latest

# Argument for running in CI
# Undefined by default, and set to `true` otherwise
ARG CI=

# Environment variables for tests
# Do if-else on CI
ENV CMOCKA_MESSAGE_OUTPUT=${CI:+XML} CMOCKA_XML_FILE=/dev/stdout

# Add software for local testing
RUN \
    if [[ -z "${CI}" ]]; then \
        apk add gdb valgrind; \
    fi

# Copy our tests into the working directory and compile them
COPY tests/ /work
RUN make \
    PREFIX=${PREFIX} \
    HOST=${HOST} \
    TARGET=${TARGET} \
    SPECS=${SPECS} \
    LNKSCRIPT=${LNKSCRIPT}

# Default command is to run the tests
CMD [ "./tests.out" ]
