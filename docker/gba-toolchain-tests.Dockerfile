# Start with our toolchain image
FROM ammrat13/gba-toolchain:latest


# Environment variables for tests
ENV CMOCKA_MESSAGE_OUTPUT=XML
ENV CMOCKA_XML_FILE=/dev/stdout

# Copy our tests into the working directory and compile them
COPY tests/ /work
RUN make

# Default command is to run the tests
CMD [ "./tests.out" ]
