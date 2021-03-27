# Start with our toolchain image
FROM ammrat13/gba-toolchain:latest

# Argument for running in CI
# Undefined by default, and set to `true` otherwise
ARG CI=

# Environment variables for tests
# Use a hack to do if-else on CI
ENV CMOCKA_MESSAGE_OUTPUT=${CI:+XML}${CI:-STDOUT}
ENV CMOCKA_XML_FILE=/dev/stdout

# Copy our tests into the working directory and compile them
COPY tests/ /work
RUN make

# Default command is to run the tests
CMD [ "./tests.out" ]
