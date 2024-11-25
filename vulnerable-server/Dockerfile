FROM gcc:latest

WORKDIR /usr/src/app

COPY . .

# Install necessary packages
RUN apt-get update && apt-get install -y \
    net-tools \
    openssh-server

# Create SSH directory and set root password
RUN mkdir /var/run/sshd
RUN echo 'root:password' | chpasswd

# Configure SSH server
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# Expose ports
EXPOSE 22
EXPOSE 9090

# Compile the threaded_serv.c
RUN gcc -o threaded_serv threaded_serv.c -lpthread

# Start SSH service and threaded server
CMD service ssh start && ./threaded_serv