# GBA Toolchain Tests

This image will test the toolchain installed in the GBA Toolchain image.
Building the image will copy over and compile the tests, which can then be run
with `docker run`.

The `Dockerfile` takes an `ARG CI`, which is empty by default. It can be set to
a non-empty value for continuous integration builds. When operating in CI, the
test results are written as JUnit XML to standard output. Otherwise, they are
written in a human-readable format to standard error. Moreover, `gdb` and
`valgrind` will be installed if not operating in CI.
