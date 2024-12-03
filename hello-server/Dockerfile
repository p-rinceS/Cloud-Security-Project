# hello_world Dockerfile
FROM debian:bullseye

# Install gcc for compiling hello.c
RUN apt-get update && apt-get install -y gcc

# Copy the hello.c file to the container
COPY hello.c /usr/src/hello.c

# Compile hello.c to create the executable
RUN gcc -o hello_world /usr/src/hello.c

# Set the entrypoint to run the hello_world program
CMD ["./hello_world"]